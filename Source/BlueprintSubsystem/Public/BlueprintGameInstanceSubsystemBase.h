// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BlueprintGameInstanceSubsystemBase.generated.h"

/**
 * Base class for a Blueprintable Game Instance Subsystem.
 */
UCLASS(Blueprintable, Abstract)
class BLUEPRINTSUBSYSTEM_API UBlueprintGameInstanceSubsystemBase : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/** 
	 * This function sets up dependencies and invokes BP_Initialize().
	 */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

protected:
	/** 
	 * List of subsystem classes that this subsystem depends on. 
	 * These will be ensured to exist before this subsystem is initialized.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TSubclassOf<UGameInstanceSubsystem>> DependencyClasses;

	UFUNCTION(BlueprintCallable, DisplayName="Get Game Instance")
	UGameInstance* BP_GetGameInstance() const;

	/** 
	 * Blueprint event triggered during initialization.  
	 */
	UFUNCTION(BlueprintImplementableEvent, DisplayName="Initialize")
	void BP_Initialize();

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	/** Override to control if the Subsystem should be created at all.
	 * For example you could only have your system created on servers.
	 * It's important to note that if using this is becomes very important to null check whenever getting the Subsystem.
	 *
	 * Note: This function is called on the CDO prior to instances being created!
	 *
	 */
	UFUNCTION(BlueprintImplementableEvent)
	bool BP_ShouldCreateSubsystem() const;
};
