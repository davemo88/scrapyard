// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrapyardGameUserSettings.h"

UScrapyardGameUserSettings::UScrapyardGameUserSettings()
{
	SetToDefaults();
}

void UScrapyardGameUserSettings::SetToDefaults()
{
	Super::SetToDefaults();

	bIsLANMatch = true;
	bIsDedicatedServer = false;
}

void UScrapyardGameUserSettings::ApplySettings(bool bCheckForCommandLineOverrides)
{
	Super::ApplySettings(bCheckForCommandLineOverrides);
}

