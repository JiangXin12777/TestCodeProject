// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorTools/Interactive/XDrawLine.h"

#include "InteractiveToolManager.h"

const FString UXDrawLineBuilder::ToolName = "X_DrawLine";

UXGraphicsTool* UXDrawLineBuilder::BuildGraphicsTool(const FToolBuilderState& SceneState) const
{
	return NewObject<UXDrawLine>(SceneState.ToolManager);
}

void UXDrawLine::Shutdown(EToolShutdownType ShutdownType)
{
	Super::Shutdown(ShutdownType);
}

void UXDrawLine::Render(IToolsContextRenderAPI* RenderAPI)
{
	Super::Render(RenderAPI);
}

bool UXDrawLine::CanAccept() const
{
	return Super::CanAccept();
}

AXGraphicsNode* UXDrawLine::CreateGraphicsNode()
{
	return Super::CreateGraphicsNode();
}
