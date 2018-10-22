// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SoloDraftGameState.generated.h"

class USoloDraft;
/**
 * 
 */
UCLASS()
class SCRAPYARD_API ASoloDraftGameState : public AGameStateBase
{
  GENERATED_BODY()

public:

  ASoloDraftGameState();
  
  UPROPERTY()
  USoloDraft* CurrentDraft;
  
};
