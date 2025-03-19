// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BlueprintSubsystemSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig)
class BLUEPRINTSUBSYSTEM_API UBlueprintSubsystemSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere)
	TArray<TSoftClassPtr<USubsystem>> BlueprintSubsystems;
};
