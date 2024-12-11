// Fill out your copyright notice in the Description page of Project Settings.


#include "SIconGeneratorViewport.h"

#include "Blueprint/UserWidget.h"
#include "IconGenerator/Settings/IconGeneratorSettings.h"
#include "IconGenerator/Viewport/IconGeneratorViewportClient.h"
#include "IconGenerator/Widget/IconGeneratorWidget.h"


SIconGeneratorViewport::SIconGeneratorViewport()
	:PreviewScene(MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues())))
{
}

void SIconGeneratorViewport::Construct(const FArguments& InArgs)
{
	SEditorViewport::Construct(SEditorViewport::FArguments());
}

TSharedPtr<FIconGeneratorViewportClient> SIconGeneratorViewport::GetViewportClient() const
{
	return ViewportClient;
}

void SIconGeneratorViewport::SetAssetData(const FAssetData& Data)
{
	AssetData = Data;
}

TSharedPtr<SWidget> SIconGeneratorViewport::BuildViewportToolbar()
{
    return SAssetEditorViewport::BuildViewportToolbar();
}


TSharedPtr<SWidget> SIconGeneratorViewport::MakeViewportToolbar()
{
	return SAssetEditorViewport::MakeViewportToolbar();
}

void SIconGeneratorViewport::PopulateViewportOverlays(TSharedRef<SOverlay> Overlay)
{
    SAssetEditorViewport::PopulateViewportOverlays(Overlay);

    UClass* WidgetClass = UIconGeneratorSettings::Get().IconGeneratorWidgetClass.LoadSynchronous();
    UIconGeneratorWidget* Widget = NewObject<UIconGeneratorWidget>(GetViewportClient()->GetWorld(), WidgetClass);
    Widget->SlateViewport = this;
    
    Overlay->AddSlot()
    .HAlign(HAlign_Fill)
    .VAlign(VAlign_Fill)
    [
		Widget->TakeWidget()
    ];

	if (AssetData.IsValid())
	{
		Widget->InitializeWithAsset(AssetData, EIconGeneratorSupportedAsset::StaticMesh);
	}
	else
	{
		Widget->InitializeWithNoAsset();
	}
}


TSharedRef<FEditorViewportClient> SIconGeneratorViewport::MakeEditorViewportClient()
{
    PreviewScene->SetFloorVisibility(false);
    ViewportClient = MakeShareable(new FIconGeneratorViewportClient(SharedThis(this), PreviewScene.ToSharedRef()));

    return ViewportClient.ToSharedRef();
}

