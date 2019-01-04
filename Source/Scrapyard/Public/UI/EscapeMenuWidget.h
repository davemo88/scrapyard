// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "EscapeMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UEscapeMenuWidget : public UUserWidget
{
  GENERATED_BODY()

protected:

  virtual void NativeConstruct() override; 
  virtual void NativeOnInitialized() override; 

  UFUNCTION()
  void Options();
  UFUNCTION()
  void QuitToMainMenu();
  UFUNCTION()
  void QuitToDesktop();

  UPROPERTY(meta=(BindWidget))
  UButton* OptionsButton;
  UPROPERTY(meta=(BindWidget))
  UButton* QuitToMainMenuButton;
  UPROPERTY(meta=(BindWidget))
  UButton* QuitToDesktopButton;
};
