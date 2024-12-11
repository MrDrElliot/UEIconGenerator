// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedPreviewScene.h"
#include "SAssetEditorViewport.h"


class UIconGeneratorWidget;
class AIconGeneratorActor;
class FIconGeneratorViewportClient;

class SIconGeneratorViewport : public SAssetEditorViewport
{
public:


	SIconGeneratorViewport();
	
	SLATE_BEGIN_ARGS(SIconGeneratorViewport) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	TSharedPtr<FIconGeneratorViewportClient> GetViewportClient() const;
	virtual TSharedPtr<SWidget> BuildViewportToolbar() override;
	virtual TSharedPtr<SWidget> MakeViewportToolbar() override;
	virtual void PopulateViewportOverlays(TSharedRef<SOverlay> Overlay) override;
	void SetAssetData(const FAssetData& Data);
	UWorld* PublicGetWorld() const { return GetWorld(); }

protected:
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

private:

	FAssetData AssetData;
	TSharedPtr<FIconGeneratorViewportClient> ViewportClient;
	TSharedPtr<FAdvancedPreviewScene> PreviewScene;
};

