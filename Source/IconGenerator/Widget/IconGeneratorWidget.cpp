// Fill out your copyright notice in the Description page of Project Settings.


#include "IconGeneratorWidget.h"

#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "IImageWrapperModule.h"
#include "ImageUtils.h"
#include "ObjectTools.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "IconGenerator/Actors/IconGeneratorActor.h"

class IImageWrapper;

UWorld* UIconGeneratorWidget::GetWorld() const
{
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		return nullptr;
	}
	return CastChecked<UWorld>(GetOuter());
}

void UIconGeneratorWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GeneratorActor)
	{
		GeneratorActor->Tick(InDeltaTime);
	}
}

void UIconGeneratorWidget::InitializeWithNoAsset_Implementation()
{
}

void UIconGeneratorWidget::InitializeWithAsset_Implementation(const FAssetData& Asset, EIconGeneratorSupportedAsset AssetType)
{
}


void UIconGeneratorWidget::GetThumbnailFromPackage(FAssetData AssetData, FThumbnailLoadDelegate OnLoaded)
{
	AsyncTask(ENamedThreads::Type::AnyBackgroundThreadNormalTask, [AssetData, OnLoaded]
	{
		FString PackageFilename;
		const FName ObjectFullName = FName(*AssetData.GetFullName());
		TSet<FName> ObjectFullNames;
		ObjectFullNames.Add(ObjectFullName);
     
		if (FPackageName::DoesPackageExist(AssetData.PackageName.ToString(), &PackageFilename))
		{
			FThumbnailMap ThumbnailMap;
			ThumbnailTools::LoadThumbnailsFromPackage(PackageFilename, ObjectFullNames,ThumbnailMap);
			FObjectThumbnail* objTN = ThumbnailMap.Find(ObjectFullName);

			IImageWrapperModule& ImageWrapperModule = FModuleManager::Get().LoadModuleChecked<IImageWrapperModule>(TEXT("ImageWrapper"));
			const TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);

			if(objTN->GetUncompressedImageData().GetData())
			{
				ImageWrapper->SetRaw(objTN->GetUncompressedImageData().GetData(), objTN->GetUncompressedImageData().Num(), objTN->GetImageWidth(), objTN->GetImageHeight(), ERGBFormat::BGRA, 8);
				const TArray64<uint8>& CompressedByteArray = ImageWrapper->GetCompressed();
				UTexture2D* Texture2D = FImageUtils::ImportBufferAsTexture2D(CompressedByteArray);

				AsyncTask(ENamedThreads::Type::GameThread, [Texture2D, OnLoaded]
				{
					OnLoaded.ExecuteIfBound(Texture2D);
				});
			}
		}
	});
}

void UIconGeneratorWidget::GetAllAssetsOfClass(const TSubclassOf<UObject> Class, TArray<FAssetData>& OutAssets)
{
	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

	FTopLevelAssetPath Path(Class->GetClassPathName());

	FARFilter Filter;
	Filter.ClassPaths.Add(Path);
	
	AssetRegistry.GetAssets(Filter, OutAssets);
	
}

bool UIconGeneratorWidget::OpenFolderDialog(const FString& DialogTitle, const FString& DefaultPath, FString& OutFolderName)
{
	void* ParentWindowPtr = FSlateApplication::Get().GetActiveTopLevelWindow()->GetNativeWindow()->GetOSWindowHandle();
	if (IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get())
	{
		DesktopPlatform->OpenDirectoryDialog(ParentWindowPtr, DialogTitle, DefaultPath, OutFolderName);
		return true;
	}

	return false;
}
