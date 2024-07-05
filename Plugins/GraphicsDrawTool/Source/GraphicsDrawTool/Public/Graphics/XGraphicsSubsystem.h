// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "XGraphicsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GRAPHICSDRAWTOOL_API UXGraphicsSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:
	// USubsystem implementation Begin
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// USubsystem implementation End
};
