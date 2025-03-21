﻿// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FBlueprintSubsystemModule : public IModuleInterface
{
	bool HandleBlueprintSubsystemSettingsSaved();
	TWeakPtr<SNotificationItem> NotificationPtr;

public:
	FSimpleDelegate OnRestartNotificationClickedDelegate;

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
