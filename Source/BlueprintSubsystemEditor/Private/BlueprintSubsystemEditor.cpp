#include "BlueprintSubsystemEditor.h"

#include "BlueprintGameInstanceSubsystemBase.h"
#include "BlueprintSubsystem.h"
#include "BlueprintSubsystemSettings.h"
#include "Kismet2/KismetEditorUtilities.h"

#define LOCTEXT_NAMESPACE "FBlueprintableSubsytemEditorModule"


void FBlueprintSubsystemEditorModule::HandleNewBlueprintableSubsystemBlueprint(UBlueprint* Blueprint)
{
	auto BlueprintClass = Blueprint->GetClass();

	//check blueprint is a subclass of UBlueprintableGameInstanceSubsystem
	if (Blueprint->GeneratedClass->IsChildOf(UBlueprintGameInstanceSubsystemBase::StaticClass()))
	{
		if (UBlueprintSubsystemSettings* Settings = GetMutableDefault<UBlueprintSubsystemSettings>(); IsValid(Settings))
		{
			bool bFound = false;
			for (auto BlueprintSubsystem : Settings->BlueprintSubsystems)
			{
				if (BlueprintSubsystem == Blueprint->GetClass())
				{
					bFound = true;
					break;
				}
			}
			if (bFound) return;
			const TSoftClassPtr<UBlueprintGameInstanceSubsystemBase> NewSubsystemClass(Blueprint->GeneratedClass);
			//how can we add a new entry to the settings?
			Settings->BlueprintSubsystems.Add(NewSubsystemClass);
			Settings->SaveConfig();
			Settings->TryUpdateDefaultConfigFile();
		}
	}
}


void FBlueprintSubsystemEditorModule::ShutdownModule()
{
}

void FBlueprintSubsystemEditorModule::StartupModule()
{
	FKismetEditorUtilities::RegisterOnBlueprintCreatedCallback(
		this,
		UBlueprintGameInstanceSubsystemBase::StaticClass(),
		FKismetEditorUtilities::FOnBlueprintCreated::CreateRaw(
			this, &FBlueprintSubsystemEditorModule::HandleNewBlueprintableSubsystemBlueprint)
	);

	//get module
	if (FBlueprintSubsystemModule* Module = FModuleManager::GetModulePtr<FBlueprintSubsystemModule>(
		"BlueprintSubsystem"))
	{
		Module->OnRestartNotificationClickedDelegate.BindLambda([]()
		{
			FUnrealEdMisc::Get().RestartEditor(false);
		});
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBlueprintSubsystemEditorModule, BlueprintableSubsystemEditor)
