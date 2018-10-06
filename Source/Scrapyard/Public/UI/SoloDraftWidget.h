// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SoloDraftWidget.generated.h"

class UYourPartsWidget;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API USoloDraftWidget : public UUserWidget
{
  GENERATED_BODY()

  TArray<UPartCardWidget*> PartCards;

  UYourPartsWidget* YourPartsWidget;
  
};
