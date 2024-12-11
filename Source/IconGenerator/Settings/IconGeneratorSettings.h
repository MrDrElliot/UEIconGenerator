// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IconGeneratorSettings.generated.h"

class AIconGeneratorActor;
class UIconGeneratorWidget;
/**
 * 
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Icon Generator Settings"), MinimalAPI)
class UIconGeneratorSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	static const UIconGeneratorSettings& Get() { return *GetDefault<UIconGeneratorSettings>(); }

	UPROPERTY(Config, EditDefaultsOnly, Category=Attribute, meta = (DisplayName = "Icon Generator Widget"))
	TSoftClassPtr<UIconGeneratorWidget> IconGeneratorWidgetClass;

	UPROPERTY(Config, EditDefaultsOnly, Category=Attribute, meta = (DisplayName = "Icon Generator Actor"))
	TSoftClassPtr<AIconGeneratorActor> IconGeneratorActor;

};
