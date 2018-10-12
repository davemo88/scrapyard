// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Levels/ScrapyardLevelScriptActor.h"
#include "SoloDraftLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API ASoloDraftLevelScriptActor : public AScrapyardLevelScriptActor
{
  GENERATED_BODY()
  
  void BeginPlay() override; 
  
};
