// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SoloDraftWidget.generated.h"

class UUserWidget;
class UYourPartsWidget;
class UUniformGridPanel;
class UHorizontalBox;
class UTextBlock;
class UPartCardWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardDraftedDelegate, UPartCardWidget*, Card);
/**
 * 
 */
UCLASS()
class SCRAPYARD_API USoloDraftWidget : public UUserWidget
{
  GENERATED_BODY()

public:

//TODO: clean up interface to this widget
  UPROPERTY(meta=(BindWidget))
  UUniformGridPanel* PackDisplayPanel;

  UPROPERTY(meta=(BindWidget))
  UYourPartsWidget* YourPartsWidget;

  UPROPERTY(meta=(BindWidget))
  UTextBlock* PickCounter;

  UFUNCTION()
  void UpdatePickCounter();

  UFUNCTION()
  void NextPack();

  void DisplayNextPack();
  
  UFUNCTION()
  void OnCardFadedOut(UPartCardWidget* PartCardWidget);

  UFUNCTION()
  void OnCardDragged(UPartCardWidget* PartCardWidget);

  FCardDraftedDelegate CardDraftedDelegate;

protected:

  void NativeConstruct() override;

  UFUNCTION()
  void OnCardDrafted(UPartCardWidget* Card);

  UFUNCTION()
  void OnCardDroppedInYourParts(UPartCardWidget* Card);
  
};
