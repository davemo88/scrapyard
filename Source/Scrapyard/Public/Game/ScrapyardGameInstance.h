// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Online.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "Parts/RobotPart.h"
#include "Parts/PartSingleton.h"
#include "ScrapyardGameInstance.generated.h"

class UScrapyardAssets;
class URobotPart;
class UPartAssets;
class URobotBodyComponent;
class USoloDraft;
class UPartAssignment;
class AScrapyardGameSession;

UCLASS()
class SCRAPYARD_API UScrapyardGameInstance : public UGameInstance
{
  GENERATED_BODY()

public:  

// will this get garbage collected? guess not i suppose
  static UScrapyardGameInstance* GameInstance;

  UScrapyardGameInstance();
  
  virtual void Init() override;

  UPROPERTY()
  UScrapyardAssets* AssetsBP;
  void InitAssetsBP();

  FStreamableManager AssetLoader;

  UPROPERTY()
  UPartSingleton* PartSingleton;

  UPROPERTY()
  UPartAssignment* PartAssignment;

  AScrapyardGameSession* GetGameSession() const;  

//TODO: how to store this to save between level changes?
  UPROPERTY()
  USoloDraft* SoloDraft;
  
};
