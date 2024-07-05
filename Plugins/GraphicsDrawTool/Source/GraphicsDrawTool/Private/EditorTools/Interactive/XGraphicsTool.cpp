// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorTools/Interactive/XGraphicsTool.h"

#include "Graphics/Interface/XDrawGraphicsCallback.h"
#include "Graphics/Interface/XGraphicsToolContext.h"

bool UXGraphicsToolBuilder::CanBuildTool(const FToolBuilderState& SceneState) const
{
	return GraphicsToolContext != nullptr && DrawGraphicsCallback != nullptr;
}

UInteractiveTool* UXGraphicsToolBuilder::BuildTool(const FToolBuilderState& SceneState) const
{
	UXGraphicsTool* XGraphicsTool = BuildGraphicsTool(SceneState);
	XGraphicsTool->SetToolContext(GraphicsToolContext);
	XGraphicsTool->SetDrawCallback(DrawGraphicsCallback);
	
	return XGraphicsTool;
}

UXGraphicsTool* UXGraphicsToolBuilder::BuildGraphicsTool(const FToolBuilderState& SceneState) const
{
	check(false);
	return nullptr;
}

void UXGraphicsTool::SetToolContext(IXGraphicsToolContext* ToolContext)
{
	GraphicsToolContext = ToolContext;
}

void UXGraphicsTool::SetDrawCallback(IXDrawGraphicsCallback* DrawCallback)
{
	DrawGraphicsCallback = DrawCallback;
}

void UXGraphicsTool::Setup()
{
	Super::Setup();

	UXSingleClickInputBehavior* LeftClickInputBehavior = NewObject<UXSingleClickInputBehavior>(this);
	LeftClickInputBehavior->Initialize(this);
	LeftClickInputBehavior->SetUseLeftMouseButton();
	AddInputBehavior(LeftClickInputBehavior);

	UXSingleClickInputBehavior* RightMouseClickInputBehavior = NewObject<UXSingleClickInputBehavior>(this);
	RightMouseClickInputBehavior->Initialize(this);
	RightMouseClickInputBehavior->SetUseRightMouseButton();
	AddInputBehavior(RightMouseClickInputBehavior);
}

void UXGraphicsTool::Shutdown(EToolShutdownType ShutdownType)
{
	Super::Shutdown(ShutdownType);
	GraphicsToolContext = nullptr;
	DrawGraphicsCallback = nullptr;
}

void UXGraphicsTool::OnTick(float DeltaTime)
{
	Super::OnTick(DeltaTime);
}

void UXGraphicsTool::Render(IToolsContextRenderAPI* RenderAPI)
{
	Super::Render(RenderAPI);
}

void UXGraphicsTool::DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI)
{
	Super::DrawHUD(Canvas, RenderAPI);
}

bool UXGraphicsTool::HasCancel() const
{
	return false;
}

bool UXGraphicsTool::HasAccept() const
{
	return false;
}

bool UXGraphicsTool::CanAccept() const
{
	return false;
}

FInputRayHit UXGraphicsTool::IsHitByClick(const FInputDeviceRay& ClickPos)
{
	return FInputRayHit(0.0f);
}

void UXGraphicsTool::OnClicked(const FInputDeviceRay& ClickPos, FKey ButtonClicked)
{
	if (ButtonClicked == EKeys::LeftMouseButton)
	{
		FHitResult HitResult;
		if (HitTest(ClickPos.WorldRay, HitResult))
		{
			OnAcceptPoint(HitResult.Location);
		}
	}
	else if (ButtonClicked == EKeys::RightMouseButton)
	{
		DrawGraphicsCallback->CancelOrCompleteActiveTool();
	}
}

FInputRayHit UXGraphicsTool::BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos)
{
	return FInputRayHit(0.0f);
}

bool UXGraphicsTool::OnUpdateHover(const FInputDeviceRay& DevicePos)
{
	FHitResult HitResult;
	if (HitTest(DevicePos.WorldRay, HitResult))
	{
		OnPreviewPoint(HitResult.Location);
		return true;
	}
	return false;
}

bool UXGraphicsTool::HitTest(const FRay& Ray, FHitResult& OutHit)
{
	UWorld* TargetWorld = GraphicsToolContext->GetWorldContext();
	FVector Start = Ray.Origin;
	FVector End = Ray.Origin + Ray.Direction * 100000000;
	if (TargetWorld->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility))
	{
		return true;
	}
	return false;
}

AXGraphicsNode* UXGraphicsTool::CreateGraphicsNode()
{
	check(false);
	return nullptr;
}

void UXGraphicsTool::CommitGraphicsNode(AXGraphicsNode* InGraphicsNode)
{
	if (CanAccept())
	{
		AcceptGraphicsNode(InGraphicsNode);
	}
	else
	{
		CancelGraphicsNode(InGraphicsNode);
	}
}

void UXGraphicsTool::AcceptGraphicsNode(AXGraphicsNode* InGraphicsNode)
{
	if (InGraphicsNode)
	{
		DrawGraphicsCallback->NotifyGraphicsOnAccept(InGraphicsNode);
	}
}

void UXGraphicsTool::CancelGraphicsNode(AXGraphicsNode* InGraphicsNode)
{
	if (InGraphicsNode)
	{
		DrawGraphicsCallback->NotifyGraphicsOnCancel(InGraphicsNode);
	}
}

void UXGraphicsTool::OnAcceptPoint(const FVector& Point)
{
	
}

void UXGraphicsTool::OnPreviewPoint(const FVector& Point)
{
}
