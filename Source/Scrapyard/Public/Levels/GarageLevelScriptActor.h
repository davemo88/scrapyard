// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Levels/ScrapyardLevelScriptActor.h"
#include "GarageLevelScriptActor.generated.h"

class USoloDraft;
class ARobotBodyGarage;
class ARobotPartActor;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AGarageLevelScriptActor : public AScrapyardLevelScriptActor
{
  GENERATED_BODY()

  void BeginPlay() override;

  USoloDraft* GetCurrentSoloDraft();

  void SpawnRobotBodyGarage();

  USoloDraft* SoloDraft;

  UFUNCTION()
  void AssignPart(URobotPart* Part);

  TArray<ARobotPartActor*> DisplayedParts;

  ARobotBodyGarage* RobotBodyGarage;

public:

  ARobotBodyGarage* GetRobotBodyGarage();

};
