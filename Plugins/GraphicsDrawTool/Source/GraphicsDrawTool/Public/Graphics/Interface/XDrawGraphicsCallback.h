// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XDrawGraphicsCallback.generated.h"

class AXGraphicsNode;

UINTERFACE(MinimalAPI)
class UXDrawGraphicsCallback : public UInterface
{
	GENERATED_BODY()
};

/** 绘制回调接口 */
class GRAPHICSDRAWTOOL_API IXDrawGraphicsCallback
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void NotifyGraphicsOnAccept(AXGraphicsNode* GraphicsNode) = 0;
	UFUNCTION()
	virtual void NotifyGraphicsOnCancel(AXGraphicsNode* GraphicsNode) = 0;
	UFUNCTION()
	virtual bool CancelOrCompleteActiveTool() = 0;
};