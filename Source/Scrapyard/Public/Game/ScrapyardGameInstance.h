// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Online.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
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
  UScrapyardGameInstance();

  FStreamableManager AssetLoader;

  UPROPERTY()
  const UScrapyardDefaultAssets* DefaultAssetsBP;

//  UPROPERTY()
//  URobotPartAssets* RobotPartAssetsBP;
//  UPROPERTY()
//  TMap<uint32, URobotPart*> PartDB;

//TODO: shouldn't be stored here because game instance doesn't replicate
  UPROPERTY()
  USoloDraft* SoloDraft;

  UPROPERTY()
  URobotPartAssignment* PartAssignment;

  AScrapyardGameSession* GetGameSession() const;  

  virtual void Init() override;
  virtual void Shutdown() override;
  virtual void StartGameInstance() override;

//  void InitPartDB();
  
};
