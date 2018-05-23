// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Online.h"
#include "Engine/GameInstance.h"
#include "Containers/Ticker.h"
#include "Robots/RobotPartAssignment.h"
#include "Online/ScrapyardGameSession.h"
#include "SoloDraft.h"
#include "ScrapyardGameInstance.generated.h"

class AScrapyardGameSession;

UCLASS()
class SCRAPYARD_API UScrapyardGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:	
	UScrapyardGameInstance();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URobotPartAssignment* RobotPartAssignment;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USoloDraft* SoloDraft;

	AScrapyardGameSession* GetGameSession() const;

	virtual void Init() override;
	virtual void Shutdown() override;
	FGameInstancePIEResult StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params) override;
	virtual void StartGameInstance() override;
	
};