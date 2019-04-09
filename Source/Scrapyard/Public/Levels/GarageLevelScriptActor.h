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

public:

  void BeginPlay() override;

  USoloDraft* GetCurrentSoloDraft() const;

  void SpawnRobotBodyGarage();

  USoloDraft* SoloDraft;

//  UFUNCTION()
//  void AssignPart(URobotPart* Part);

  TArray<ARobotPartActor*> DisplayedParts;

  ARobotBodyGarage* RobotBodyGarage;

  ARobotBodyGarage* GetRobotBodyGarage() const;

};
