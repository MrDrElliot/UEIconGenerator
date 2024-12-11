// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneCaptureComponent2D.h"

#include "IconGeneratorActor.generated.h"

class USpringArmComponent;

UCLASS()
class ICONGENERATOR_API AIconGeneratorActor : public AActor
{
	GENERATED_BODY()

public:
	
	AIconGeneratorActor();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "IconGenerator")
	void SetCameraDistance(float Delta, float Step = 2.0f);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IconGenerator")
	void OnMouseMove(FVector2D Delta, float Sensitivity = 1.0f);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IconGenerator")
	void SetAssetData(const FAssetData& AssetData);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IconGenerator")
	void SetFieldOfView(float FOV);

	UFUNCTION(BlueprintCallable, Category = "IconGenerator")
	FORCEINLINE void SetOrthoWidth(float Width);
	
	UFUNCTION(BlueprintCallable, Category = "IconGenerator")
	FORCEINLINE void SetProjectionMode(ECameraProjectionMode::Type InProjectionMode);
	

	UFUNCTION(BlueprintCallable, Category = "IconGenerator")
	void ForceCapture();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneCaptureComponent2D> SceneCaptureComponent2D;

};


