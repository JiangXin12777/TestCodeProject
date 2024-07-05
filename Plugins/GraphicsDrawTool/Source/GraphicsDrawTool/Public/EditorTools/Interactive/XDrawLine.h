// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XGraphicsTool.h"
#include "XDrawLine.generated.h"

UCLASS()
class GRAPHICSDRAWTOOL_API UXDrawLineBuilder : public UXGraphicsToolBuilder
{
	GENERATED_BODY()
public:
	static const FString ToolName;
	
protected:
	virtual UXGraphicsTool* BuildGraphicsTool(const FToolBuilderState& SceneState) const override;
};

/**
 * 
 */
UCLASS()
class GRAPHICSDRAWTOOL_API UXDrawLine : public UXGraphicsTool
{
	GENERATED_BODY()

protected:
	virtual void Shutdown(EToolShutdownType ShutdownType) override;
	virtual void Render(IToolsContextRenderAPI* RenderAPI) override;
	virtual bool CanAccept() const override;

	virtual AXGraphicsNode* CreateGraphicsNode() override;
};
