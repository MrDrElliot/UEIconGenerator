// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AdvancedPreviewScene.h"
#include "EditorViewportClient.h"
#include "Slate/SIconGeneratorViewport.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FIconGeneratorTickDelegate, float);

class FAdvancedPreviewScene;

class FIconGeneratorViewportClient : public FEditorViewportClient
{
public:
	FIconGeneratorViewportClient(const TSharedRef<SIconGeneratorViewport>& Viewport, const TSharedRef<FAdvancedPreviewScene>& InPreviewScene)
	: FEditorViewportClient(nullptr, &InPreviewScene.Get(), StaticCastSharedRef<SEditorViewport>(Viewport))
	{
		CameraSpeedScalar = 0.0f;
		SetRealtime(true);
		SetGameView(true);
		FEditorViewportClient::SetCameraLock();
		SetViewLocation(FVector(0, 0, 400));
		SetViewRotation(FRotator(0, 0, 0));
		FEditorViewportClient::SetViewMode(VMI_Lit);
	}

	virtual void MouseMove(FViewport* InViewport, int32 X, int32 Y) override
	{
		// Intentionally overriden.
	}

	virtual void Tick(float DeltaSeconds) override
	{
		FEditorViewportClient::Tick(DeltaSeconds);
		OnTick.Broadcast(DeltaSeconds);
	}

	virtual FLinearColor GetBackgroundColor() const override
	{
		return FLinearColor::Black;
	}

	FIconGeneratorTickDelegate OnTick;
};

