// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorTools/Behaviors/XSingleClickInputBehavior.h"

UXSingleClickInputBehavior::UXSingleClickInputBehavior()
	: Super()
	, bHitTestOnRelease(false)
	, Target(nullptr)
{
}

void UXSingleClickInputBehavior::Initialize(IXClickBehaviorTarget* InTarget)
{
	this->Target = InTarget;
}

FKey UXSingleClickInputBehavior::GetKey(const FInputDeviceState& Input)
{
	return GetButtonStateFunc(Input).Button;
}

FInputCaptureRequest UXSingleClickInputBehavior::WantsCapture(const FInputDeviceState& Input)
{
	if (IsPressed(Input) && (ModifierCheckFunc == nullptr || ModifierCheckFunc(Input)) )
	{
		FInputRayHit HitResult = Target->IsHitByClick(GetDeviceRay(Input));
		if (HitResult.bHit)
		{
			return FInputCaptureRequest::Begin(this, EInputCaptureSide::Any, HitResult.HitDepth);
		}
	}
	return FInputCaptureRequest::Ignore();
}

FInputCaptureUpdate UXSingleClickInputBehavior::BeginCapture(const FInputDeviceState& Input, EInputCaptureSide eSide)
{
	Modifiers.UpdateModifiers(Input, Target);
	return FInputCaptureUpdate::Begin(this, EInputCaptureSide::Any);
}

FInputCaptureUpdate UXSingleClickInputBehavior::UpdateCapture(const FInputDeviceState& Input,
	const FInputCaptureData& Data)
{
	Modifiers.UpdateModifiers(Input, Target);
	if (IsReleased(Input))
	{
		if (bHitTestOnRelease == false || 
			Target->IsHitByClick(GetDeviceRay(Input)).bHit )
		{
			Clicked(Input, Data);
		}

		return FInputCaptureUpdate::End();
	}

	return FInputCaptureUpdate::Continue();
}

void UXSingleClickInputBehavior::ForceEndCapture(const FInputCaptureData& Data)
{
	Super::ForceEndCapture(Data);
}

void UXSingleClickInputBehavior::Clicked(const FInputDeviceState& Input, const FInputCaptureData& Data)
{
	check(Target != nullptr)
	Target->OnClicked(GetDeviceRay(Input), GetKey(Input));
}
