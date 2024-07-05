// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBehaviors/AnyButtonInputBehavior.h"
#include "BaseBehaviors/BehaviorTargetInterfaces.h"
#include "BaseBehaviors/InputBehaviorModifierStates.h"
#include "XSingleClickInputBehavior.generated.h"

class IXClickBehaviorTarget : public IModifierToggleBehaviorTarget
{
public:
	virtual ~IXClickBehaviorTarget() override {}

	/**
	* Test if target is hit by a click
	* @param ClickPos device position/ray at click point
	* @return hit information at this point
	*/
	virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) = 0;
	
	/**
	* Notify Target that click ocurred
	* @param ClickPos device position/ray at click point
	* @param ButtonClicked 
	*/
	virtual void OnClicked(const FInputDeviceRay& ClickPos, FKey ButtonClicked) = 0;
};

/**
 * 
 */
UCLASS()
class GRAPHICSDRAWTOOL_API UXSingleClickInputBehavior : public UAnyButtonInputBehavior
{
	GENERATED_BODY()

public:
	UXSingleClickInputBehavior();
	
	/**
	* Initialize this behavior with the given Target
	* @param InTarget implementor of hit-test and on-clicked functions
	*/
	virtual void Initialize(IXClickBehaviorTarget* InTarget);

	virtual FKey GetKey(const FInputDeviceState& Input);

	/**
	* WantsCapture() will only return capture request if this function returns true (or is null)
	*/
	TFunction<bool(const FInputDeviceState&)> ModifierCheckFunc = nullptr;


	// UInputBehavior implementation

	virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& Input) override;
	virtual FInputCaptureUpdate BeginCapture(const FInputDeviceState& Input, EInputCaptureSide eSide) override;
	virtual FInputCaptureUpdate UpdateCapture(const FInputDeviceState& Input, const FInputCaptureData& Data) override;
	virtual void ForceEndCapture(const FInputCaptureData& Data) override;


public:
	/** Hit-test is repeated on release (standard behavior). If false, */
	UPROPERTY()
	bool bHitTestOnRelease;

	/**
	* The modifier set for this behavior
	*/
	FInputBehaviorModifierStates Modifiers;


protected:
	/** Click Target object */
	IXClickBehaviorTarget* Target;

	/**
	* Internal function that forwards click evens to Target::OnClicked, you can customize behavior here
	*/
	virtual void Clicked(const FInputDeviceState& Input, const FInputCaptureData& Data);
};
