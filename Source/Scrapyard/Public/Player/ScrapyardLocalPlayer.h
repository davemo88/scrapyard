// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LocalPlayer.h"
#include "ScrapyardLocalPlayer.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UScrapyardLocalPlayer : public ULocalPlayer
{
	GENERATED_BODY()

public:

	virtual FString GetNickname() const;

};
