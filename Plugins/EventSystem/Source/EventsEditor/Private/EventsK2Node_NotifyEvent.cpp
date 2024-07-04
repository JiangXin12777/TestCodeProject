// Copyright 2019 - 2021, butterfly, Event System Plugin, All Rights Reserved.

#include "EventsK2Node_NotifyEvent.h"
#include "EdGraphSchema_K2.h"
#include "Engine/Blueprint.h"
#include "BlueprintNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintEventLibrary.h"
#include "EventsManager.h"
#include "EventSystemBPLibrary.h"
#include "K2Node_CallFunction.h"
#include "KismetCompilerMisc.h"
#include "KismetCompiler.h"
#include "Kismet/KismetSystemLibrary.h"


UEventsK2Node_NotifyEvent::UEventsK2Node_NotifyEvent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) 
{
	OrphanedPinSaveMode = ESaveOrphanPinMode::SaveNone; 
}

UEdGraphPin* UEventsK2Node_NotifyEvent::CreatePinFromUserDefinition(const TSharedPtr<FUserPinInfo> NewPinInfo)
{
	UEdGraphPin* Pin = CreatePin(EGPD_Input, NewPinInfo->PinType, NewPinInfo->PinName);
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	K2Schema->SetPinAutogeneratedDefaultValue(Pin,NewPinInfo->PinDefaultValue);
	return Pin;
}

void UEventsK2Node_NotifyEvent::AddInnerPin(FName PinName, const FEdGraphPinType& PinType)
{
	CreateUserDefinedPin(PinName, PinType);
}

void UEventsK2Node_NotifyEvent::ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);
	static const FName FuncName = GET_FUNCTION_NAME_CHECKED(UEventSystemBPLibrary, NotifyEventByKeyVariadic);

	UEventsK2Node_NotifyEvent* SpawnNode = this;
	UEdGraphPin* SpawnEventExec = GetExecPin();
	UEdGraphPin* SpawnMsgPin = GetEventPin();
	UEdGraphPin* SpawnSenderPin = GetSelfPin();
	UEdGraphPin* SpawnNodeThen = GetThenPin();
	UEdGraphPin* SwpanListenerPin = GetListenerPin();


	UK2Node_CallFunction* CallNotifyFuncNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(SpawnNode, SourceGraph);
	CallNotifyFuncNode->FunctionReference.SetExternalMember(FuncName, UEventSystemBPLibrary::StaticClass());
	CallNotifyFuncNode->AllocateDefaultPins();
	
	bool bError = true;

	UEdGraphPin* CallExecPin = CallNotifyFuncNode->GetExecPin();
	bError &= CompilerContext.MovePinLinksToIntermediate(*SpawnEventExec, *CallExecPin).CanSafeConnect();

	UEdGraphPin* CallMessageIdPin = CallNotifyFuncNode->FindPinChecked(TEXT("MessageId"));
	bError &= CompilerContext.MovePinLinksToIntermediate(*SpawnMsgPin, *CallMessageIdPin).CanSafeConnect();

	UEdGraphPin* CallSenderPin = CallNotifyFuncNode->FindPinChecked(SenderPinName);
	bError &= CompilerContext.MovePinLinksToIntermediate(*SpawnSenderPin, *CallSenderPin).CanSafeConnect();

	UEdGraphPin* CallListenerPin = CallNotifyFuncNode->FindPinChecked(ListenerPinName);
	bError &= CompilerContext.MovePinLinksToIntermediate(*SwpanListenerPin, *CallListenerPin).CanSafeConnect();

	UEdGraphPin* CallThen = CallNotifyFuncNode->GetThenPin();
	bError &= CompilerContext.MovePinLinksToIntermediate(*SpawnNodeThen, *CallThen).CanSafeConnect();

	const UEdGraphSchema_K2* K2Schema = CompilerContext.GetSchema();
	for (int32 ArgIdx = 0; ArgIdx < PinNames.Num(); ++ArgIdx)
	{
		UEdGraphPin* ParameterPin = FindPin(PinNames[ArgIdx]);
		if (ParameterPin)
		{
			bool bHasConnection = ParameterPin->HasAnyConnections();
			FString DefaultValue = ParameterPin->GetDefaultAsString();
			auto InputPin = CallNotifyFuncNode->CreatePin(EGPD_Input, ParameterPin->PinType, ParameterPin->PinName);
			FName DefaultFuncName;
			if (bHasConnection == false)
			{
				if (ParameterPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Boolean)
				{
					DefaultFuncName = GET_FUNCTION_NAME_CHECKED(UEventSystemBPLibrary, LocalBool);
				}
				else if (ParameterPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Text)
				{
					DefaultFuncName = GET_FUNCTION_NAME_CHECKED(UEventSystemBPLibrary, LocalText);
				}
				else if (ParameterPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Int)
				{
					DefaultFuncName = GET_FUNCTION_NAME_CHECKED(UEventSystemBPLibrary, LocalInt);
				}
				else if (ParameterPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Int64)
				{
					DefaultFuncName = GET_FUNCTION_NAME_CHECKED(UEventSystemBPLibrary, LocalInt64);
				}
				else if (ParameterPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Float)
				{
					DefaultFuncName = GET_FUNCTION_NAME_CHECKED(UEventSystemBPLibrary, Localfloat);
				}
				else if (ParameterPin->PinType.PinCategory == UEdGraphSchema_K2::PC_String )
				{
					DefaultFuncName = GET_FUNCTION_NAME_CHECKED(UEventSystemBPLibrary, LocalFString);
				}
				else if (ParameterPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Name)
				{
					DefaultFuncName = GET_FUNCTION_NAME_CHECKED(UEventSystemBPLibrary, LocalName);
				}
				else if (ParameterPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
				{
					// If you update this logic you'll probably need to update UEdGraphSchema_K2::ShouldHidePinDefaultValue!
					UScriptStruct* ColorStruct = TBaseStructure<FLinearColor>::Get();
					UScriptStruct* VectorStruct = TBaseStructure<FVector>::Get();
					UScriptStruct* Vector2DStruct = TBaseStructure<FVector2D>::Get();
					UScriptStruct* RotatorStruct = TBaseStructure<FRotator>::Get();

					if (ParameterPin->PinType.PinSubCategoryObject == ColorStruct)
					{
						DefaultFuncName = GET_FUNCTION_NAME_CHECKED(UEventSystemBPLibrary, LocalLinearColor);
					}
					else if ((ParameterPin->PinType.PinSubCategoryObject == VectorStruct))
					{
						DefaultFuncName = GET_FUNCTION_NAME_CHECKED(UEventSystemBPLibrary, LocalVector);
					}
					else if (ParameterPin->PinType.PinSubCategoryObject == RotatorStruct)
					{
						DefaultFuncName = GET_FUNCTION_NAME_CHECKED(UEventSystemBPLibrary, LocalRotator);
					}
					else if (ParameterPin->PinType.PinSubCategoryObject == Vector2DStruct)
					{
						DefaultFuncName = GET_FUNCTION_NAME_CHECKED(UEventSystemBPLibrary, LocalVector2D);
					}
				}
				else if (ParameterPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Byte)
				{
					UEnum* EnumPtr = Cast<UEnum>(ParameterPin->PinType.PinSubCategoryObject.Get());
					if (EnumPtr)
					{
						int32 EnumIndex = EnumPtr->GetIndexByNameString(DefaultValue);
						if (EnumIndex == INDEX_NONE)
						{
							EnumIndex = 0;
						}
						DefaultValue = FString::Printf(TEXT("%d"), EnumIndex);
					}
					DefaultFuncName = GET_FUNCTION_NAME_CHECKED(UEventSystemBPLibrary, Localuint8);
				}
				
			}
			if (DefaultFuncName.IsNone() == false)
			{
				UK2Node_CallFunction* LocalValueNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
				LocalValueNode->FunctionReference.SetExternalMember(DefaultFuncName, UEventSystemBPLibrary::StaticClass());
				LocalValueNode->AllocateDefaultPins();
				UEdGraphPin* InValuePin = LocalValueNode->FindPin(TEXT("Value"), EGPD_Input);
				UEdGraphPin* ReValuePin = LocalValueNode->GetReturnValuePin();
				K2Schema->TrySetDefaultValue(*InValuePin, DefaultValue);
				bError &= K2Schema->TryCreateConnection(ReValuePin, InputPin);
			}
			else
			{
				bError &= CompilerContext.MovePinLinksToIntermediate(*ParameterPin, *InputPin).CanSafeConnect();
			}
		}
	}
	SpawnNode->BreakAllNodeLinks();
}


void UEventsK2Node_NotifyEvent::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
}

void UEventsK2Node_NotifyEvent::CreateNotifyListenerPin()
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	UEdGraphPin* Pin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, ListenerPinName);
	DefaultPins.Add(Pin);
	K2Schema->SetPinAutogeneratedDefaultValueBasedOnType(Pin);
}

FText UEventsK2Node_NotifyEvent::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return NSLOCTEXT("K2Node", "Notify_EVENT_Event", "Notify Event");
}

FText UEventsK2Node_NotifyEvent::GetTooltipText() const
{
	return NSLOCTEXT("K2Node", "UEventsK2Node_NotifyEvent_ToolTip", "Notify Listen Event");
}