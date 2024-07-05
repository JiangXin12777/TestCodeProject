// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveTool.h"
#include "InteractiveToolBuilder.h"
#include "EditorTools/Behaviors/XSingleClickInputBehavior.h"
#include "XGraphicsTool.generated.h"

class UXGraphicsTool;
class IXDrawGraphicsCallback;
class IXGraphicsToolContext;
class UXGraphicsNode;

/**
 * 
 */
UCLASS()
class GRAPHICSDRAWTOOL_API UXGraphicsToolBuilder : public UInteractiveToolBuilder
{
	GENERATED_BODY()
public:
	// UInteractiveToolBuilder implementation Begin
	virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;
	virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;
	// UInteractiveToolBuilder implementation End
	
protected:
	virtual UXGraphicsTool* BuildGraphicsTool(const FToolBuilderState& SceneState) const;

public:
	IXGraphicsToolContext* GraphicsToolContext = nullptr;
	IXDrawGraphicsCallback* DrawGraphicsCallback = nullptr;
};

UCLASS()
class GRAPHICSDRAWTOOL_API UXGraphicsTool
	: public UInteractiveTool
	, public IXClickBehaviorTarget
	, public IHoverBehaviorTarget
{
	GENERATED_BODY()
public:
	void SetToolContext(IXGraphicsToolContext* ToolContext);
	void SetDrawCallback(IXDrawGraphicsCallback* DrawCallback);

protected:
	// UInteractiveTool implementation Begin
	virtual void Setup() override;
	virtual void Shutdown(EToolShutdownType ShutdownType) override;
	
	virtual void OnTick(float DeltaTime) override;
	virtual void Render(IToolsContextRenderAPI* RenderAPI) override;
	virtual void DrawHUD( FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI ) override;
	
	virtual bool HasCancel() const override;
	virtual bool HasAccept() const override;
	virtual bool CanAccept() const override;
	// UInteractiveTool implementation End

	// IXClickBehaviorTarget implementation Begin
	virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;
	virtual void OnClicked(const FInputDeviceRay& ClickPos, FKey ButtonClicked) override;
	// IXClickBehaviorTarget implementation End

	// IHoverBehaviorTarget implementation Begin
	virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;
	virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override {}
	virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;
	virtual void OnEndHover() override {}
	// IHoverBehaviorTarget implementation End
	
	/** 射线检测 */
	virtual bool HitTest(const FRay& Ray, FHitResult& OutHit);

	virtual AXGraphicsNode* CreateGraphicsNode();
	virtual void CommitGraphicsNode(AXGraphicsNode* InGraphicsNode);
	virtual void AcceptGraphicsNode(AXGraphicsNode* InGraphicsNode);
	virtual void CancelGraphicsNode(AXGraphicsNode* InGraphicsNode);

	virtual void OnAcceptPoint(const FVector& Point);
	virtual void OnPreviewPoint(const FVector& Point);

protected:
	IXGraphicsToolContext* GraphicsToolContext = nullptr;
	IXDrawGraphicsCallback* DrawGraphicsCallback = nullptr;
};
