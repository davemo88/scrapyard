// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "ScrapyardGameUserSettings.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UScrapyardGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:

	UScrapyardGameUserSettings();
	
	virtual void ApplySettings(bool bCheckForCommandLineOverrides) override;

	virtual void SetToDefaults() override;

	bool IsLanMatch() const { return bIsLANMatch; }

	void SetLanMatch(bool InbIsLanMatch) { bIsLANMatch = InbIsLanMatch; }
	
	bool IsDedicatedServer() const { return bIsDedicatedServer; }

	void SetDedicatedServer(bool InbIsDedicatedServer) { bIsDedicatedServer = InbIsDedicatedServer; }

private:

	UPROPERTY(config)
	bool bIsLANMatch;

	UPROPERTY(config)
	bool bIsDedicatedServer;
	
};
