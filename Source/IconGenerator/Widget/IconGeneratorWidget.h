// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "Blueprint/UserWidget.h"
#include "IconGenerator/Viewport/IconGeneratorViewportClient.h"
#include "IconGenerator/Viewport/Slate/SIconGeneratorViewport.h"

#include "IconGeneratorWidget.generated.h"

class AIconGeneratorActor;
class SIconGeneratorViewport;

UENUM(BlueprintType)
enum class EIconGeneratorSupportedAsset : uint8
{
	StaticMesh,
	SkeletalMesh,
	BlueprintActor,
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FThumbnailLoadDelegate, UTexture2D*, Texture);


UCLASS(Abstract, Config = Editor)
class ICONGENERATOR_API UIconGeneratorWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual UWorld* GetWorld() const override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, Category = "IconGenerator")
	void InitializeWithAsset(const FAssetData& Asset, EIconGeneratorSupportedAsset AssetType);
	
	UFUNCTION(BlueprintNativeEvent, Category = "IconGenerator")
	void InitializeWithNoAsset();

	// Allows access to some editor functionality.
	virtual bool IsEditorUtility() const override { return true; }

	UFUNCTION(BlueprintCallable, Category = "Thumbnail")
	static void GetThumbnailFromPackage(FAssetData AssetData, FThumbnailLoadDelegate OnLoaded);

	UFUNCTION(BlueprintCallable, Category = "Assets")
	static void GetAllAssetsOfClass(TSubclassOf<UObject> Class, TArray<FAssetData>& OutAssets);

	// Open Folder Dialog
	UFUNCTION(BlueprintCallable, Category = "Assets")
	static bool OpenFolderDialog(const FString& DialogTitle, const FString& DefaultPath, FString& OutFolderName);
	
	UFUNCTION(BlueprintPure, Category = "Position")
	FVector GetViewLocation() const { return SlateViewport ? SlateViewport->GetViewportClient()->GetViewLocation() : FVector::ZeroVector; }

	UFUNCTION(BlueprintPure, Category = "Rotation")
	FRotator GetViewRotation() const { return SlateViewport ? SlateViewport->GetViewportClient()->GetViewRotation() : FRotator::ZeroRotator; }

	SIconGeneratorViewport* SlateViewport;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Icon")
	TObjectPtr<AIconGeneratorActor> GeneratorActor;

};
