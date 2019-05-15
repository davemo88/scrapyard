// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Online.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "Parts/RobotPart.h"
#include "Parts/RobotPartSingleton.h"
#include "ScrapyardGameInstance.generated.h"

class UScrapyardAssets;
class URobotPart;
class URobotPartAssets;
class URobotBodyComponent;
class USoloDraft;
class URobotPartAssignment;
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

//TODO: shouldn't be stored here because game instance doesn't replicate
  UPROPERTY()
  USoloDraft* SoloDraft;

  UPROPERTY()
  URobotPartSingleton* RobotPartSingleton;

  UPROPERTY()
  URobotPartAssignment* PartAssignment;

  AScrapyardGameSession* GetGameSession() const;  
  
};
