// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FIconGeneratorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static void ExtendContextMenu();

	static void OpenIconGenerator();
	void RegisterGameEditorMenus();

	TSharedRef<SDockTab> OpenIconGenerator(const FSpawnTabArgs& Args);
	TSharedPtr<SWidget> SummonIconGenerator(const FAssetData& AssetData = FAssetData());

	static void OpenStaticMeshInIconGenerator(const FAssetData& AssetData);
	static void OpenSkeletalMeshInIconGenerator(const FAssetData& AssetData);
	static void OpenBlueprintInIconGenerator(const FAssetData& AssetData);


private:

	TWeakPtr<SDockTab> IconGeneratorTab;


};
