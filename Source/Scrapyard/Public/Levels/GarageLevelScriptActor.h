// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Levels/ScrapyardLevelScriptActor.h"
#include "GarageLevelScriptActor.generated.h"

class USoloDraft;
class ARobotCharacter;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AGarageLevelScriptActor : public AScrapyardLevelScriptActor
{
  GENERATED_BODY()

public:

  void BeginPlay() override;

  ARobotCharacter* GetRobotCharacter();

protected:

  void SpawnRobotCharacter();

  UPROPERTY()
  ARobotCharacter* RobotCharacter;

};
