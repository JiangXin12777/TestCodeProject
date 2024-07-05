// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XGraphicsToolContext.generated.h"

UINTERFACE(MinimalAPI)
class UXGraphicsToolContext : public UInterface
{
	GENERATED_BODY()
};

class GRAPHICSDRAWTOOL_API IXGraphicsToolContext
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual UWorld* GetWorldContext() const = 0;
};