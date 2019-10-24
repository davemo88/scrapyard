// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "ScrapyardPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AScrapyardPlayerStart : public APlayerStart
{
  GENERATED_BODY()
  
public:

  bool bAvailable = true;
  
};
