// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Online.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "Parts/RobotPart.h"
#include "ScrapyardGameInstance.generated.h"

class UScrapyardDefaultAssets;
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
  URobotPartAssets* RobotPartAssetsBP;
  void InitRobotPartAssetsBP();

  UPROPERTY()
  UScrapyardDefaultAssets* DefaultAssetsBP;
  void InitDefaultAssetsBP();

  UPROPERTY()
  FPartDatabase PartDB;
  void InitPartDB();

  FManufacturers Manufacturers;

  FStreamableManager AssetLoader;

//  UPROPERTY()
//  URobotPartAssets* RobotPartAssetsBP;

//TODO: shouldn't be stored here because game instance doesn't replicate
  UPROPERTY()
  USoloDraft* SoloDraft;

  UPROPERTY()
  URobotPartAssignment* PartAssignment;

  AScrapyardGameSession* GetGameSession() const;  
  
};
