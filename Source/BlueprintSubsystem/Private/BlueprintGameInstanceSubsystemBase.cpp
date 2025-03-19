// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintGameInstanceSubsystemBase.h"

void UBlueprintGameInstanceSubsystemBase::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	for (auto& DependencyClass : DependencyClasses)
	{
		Collection.InitializeDependency(DependencyClass);
	}
	BP_Initialize();
}

UGameInstance* UBlueprintGameInstanceSubsystemBase::BP_GetGameInstance() const
{
	return GetGameInstance();
}

bool UBlueprintGameInstanceSubsystemBase::ShouldCreateSubsystem(UObject* Outer) const
{
	if (GetClass()->IsFunctionImplementedInScript(
		GET_FUNCTION_NAME_CHECKED(UBlueprintGameInstanceSubsystemBase, BP_ShouldCreateSubsystem)))
	{
		return BP_ShouldCreateSubsystem();
	}
	return Super::ShouldCreateSubsystem(Outer);
}

bool UBlueprintGameInstanceSubsystemBase::IsInstantiated() const
{
	return !HasAllFlags(RF_ClassDefaultObject);
}

class UWorld* UBlueprintGameInstanceSubsystemBase::GetWorld() const
{
	if (!IsInstantiated())
	{
		// If we are a CDO, we must return nullptr instead of calling Outer->GetWorld() to fool UObject::ImplementsGetWorld.
		return nullptr;
	}
	return GetOuter()->GetWorld();
}
