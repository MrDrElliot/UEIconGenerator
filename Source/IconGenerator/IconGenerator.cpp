// Copyright Epic Games, Inc. All Rights Reserved.

#include "IconGenerator.h"

#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "Editor/WorkspaceMenuStructure/Public/WorkspaceMenuStructure.h"
#include "Editor/WorkspaceMenuStructure/Public/WorkspaceMenuStructureModule.h"
#include "Viewport/Slate/SIconGeneratorViewport.h"

#define LOCTEXT_NAMESPACE "FIconGeneratorModule"

void FIconGeneratorModule::StartupModule()
{
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateStatic(&FIconGeneratorModule::ExtendContextMenu));
	
	if(FSlateApplication::IsInitialized())
	{
		const auto Delegate = FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FIconGeneratorModule::RegisterGameEditorMenus);
		UToolMenus::RegisterStartupCallback(Delegate);
	}
}

void FIconGeneratorModule::ShutdownModule()
{
	if (FSlateApplication::IsInitialized())
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner("IconGeneratorTab");
	}

	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
}

void FIconGeneratorModule::ExtendContextMenu()
{
	TArray<FName> AssetTypesToExtend =
	{
		"ContentBrowser.AssetContextMenu.StaticMesh",
		"ContentBrowser.AssetContextMenu.SkeletalMesh",
		"ContentBrowser.AssetContextMenu.Blueprint"
	};

	for (const FName& AssetTypeMenu : AssetTypesToExtend)
	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu(AssetTypeMenu);
		if (!Menu) continue;

		FToolMenuSection& Section = Menu->AddSection("AssetContextIconGenerator", LOCTEXT("FIconGeneratorModule", "Icon Generator"));

		Section.AddMenuEntry
		(
			FName("IconGenerator"),
			LOCTEXT("FIconGeneratorModule", "Open in Icon Generator"),
			LOCTEXT("FIconGeneratorModule", "Opens this asset in the icon generator"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "AnimEditor.FilterSearch"),
			FUIAction(FExecuteAction::CreateStatic(&FIconGeneratorModule::OpenIconGenerator))
		);
	}
}

void FIconGeneratorModule::OpenIconGenerator()
{
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	TArray<FAssetData> SelectedAssets;
	ContentBrowserModule.Get().GetSelectedAssets(SelectedAssets);

	if (SelectedAssets.Num() == 0)
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("No assets selected!"));
		return;
	}

	for (const FAssetData& AssetData : SelectedAssets)
	{
		if (AssetData.AssetClassPath == UStaticMesh::StaticClass()->GetClassPathName())
		{
			OpenStaticMeshInIconGenerator(AssetData);
			return;
		}
		else if (AssetData.AssetClassPath == USkeletalMesh::StaticClass()->GetClassPathName())
		{
			OpenSkeletalMeshInIconGenerator(AssetData);
			return;
		}
		else if (AssetData.AssetClassPath == UBlueprint::StaticClass()->GetClassPathName())
		{
			OpenBlueprintInIconGenerator(AssetData);
			return;
		}
		else
		{
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Unsupported asset type!"));
		}
	}
}

void FIconGeneratorModule::RegisterGameEditorMenus()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner( FName(TEXT("IconGeneratorTab")), FOnSpawnTab::CreateRaw(this, &FIconGeneratorModule::OpenIconGenerator))
	.SetDisplayName(NSLOCTEXT("FIconGeneratorModule", "IconGeneratorTitle", "Icon Generator"))
	.SetTooltipText(NSLOCTEXT("FIconGeneratorModule", "IconGeneratorTooltipText", "Open icon generator"))
	.SetGroup(WorkspaceMenu::GetMenuStructure().GetToolsCategory())
	.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "Symbols.SearchGlass"));
}

TSharedRef<SDockTab> FIconGeneratorModule::OpenIconGenerator(const FSpawnTabArgs& Args)
{
	return SAssignNew(IconGeneratorTab, SDockTab)
	.TabRole(NomadTab)
	[
		SummonIconGenerator().ToSharedRef()
	];
}

TSharedPtr<SWidget> FIconGeneratorModule::SummonIconGenerator(const FAssetData& AssetData)
{
	TSharedPtr<SWidget> ReturnWidget;
	if(IsInGameThread())
	{
		return SNew(SIconGeneratorViewport);
	}
	return ReturnWidget;
}

void FIconGeneratorModule::OpenStaticMeshInIconGenerator(const FAssetData& AssetData)
{
	TSharedPtr<SDockTab> DockTab = FGlobalTabmanager::Get()->TryInvokeTab(FName(TEXT("IconGeneratorTab")));

	TSharedRef<SIconGeneratorViewport> IconViewport = StaticCastSharedRef<SIconGeneratorViewport>(DockTab->GetContent());
	IconViewport->SetAssetData(AssetData);
}

void FIconGeneratorModule::OpenSkeletalMeshInIconGenerator(const FAssetData& AssetData)
{
	TSharedPtr<SDockTab> DockTab = FGlobalTabmanager::Get()->TryInvokeTab(FName(TEXT("IconGeneratorTab")));

	TSharedRef<SIconGeneratorViewport> IconViewport = StaticCastSharedRef<SIconGeneratorViewport>(DockTab->GetContent());
	IconViewport->SetAssetData(AssetData);
}

void FIconGeneratorModule::OpenBlueprintInIconGenerator(const FAssetData& AssetData)
{
	TSharedPtr<SDockTab> DockTab = FGlobalTabmanager::Get()->TryInvokeTab(FName(TEXT("IconGeneratorTab")));

	TSharedRef<SIconGeneratorViewport> IconViewport = StaticCastSharedRef<SIconGeneratorViewport>(DockTab->GetContent());
	IconViewport->SetAssetData(AssetData);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FIconGeneratorModule, IconGenerator)