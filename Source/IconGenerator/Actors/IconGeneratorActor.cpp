// Fill out your copyright notice in the Description page of Project Settings.


#include "IconGeneratorActor.h"

#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/SpringArmComponent.h"


AIconGeneratorActor::AIconGeneratorActor()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneRoot);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(SceneRoot);

	SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent2D"));
	SceneCaptureComponent2D->SetupAttachment(SpringArmComponent, TEXT("SpringEndPoint"));
}

void AIconGeneratorActor::SetCameraDistance(float Delta, float Step)
{
	SpringArmComponent->TargetArmLength = SpringArmComponent->TargetArmLength + (Delta * Step);
	SpringArmComponent->TickComponent(Delta, LEVELTICK_All, nullptr);
	
	ForceCapture();
}

void AIconGeneratorActor::OnMouseMove_Implementation(FVector2D Delta, float Sensitivity)
{
}

void AIconGeneratorActor::SetAssetData_Implementation(const FAssetData& AssetData)
{
}

void AIconGeneratorActor::SetFieldOfView_Implementation(float FOV)
{
	SceneCaptureComponent2D->FOVAngle = FOV;
	ForceCapture();
}

void AIconGeneratorActor::SetOrthoWidth(float Width)
{
	SceneCaptureComponent2D->OrthoWidth = Width;
	ForceCapture();
}

void AIconGeneratorActor::SetProjectionMode(ECameraProjectionMode::Type InProjectionMode)
{
	SceneCaptureComponent2D->ProjectionType = InProjectionMode;
	ForceCapture();
}

void AIconGeneratorActor::ForceCapture()
{
	SceneCaptureComponent2D->CaptureScene();
}

void AIconGeneratorActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}
