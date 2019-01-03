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

public:
  UPROPERTY(meta=(BindWidget))
  UButton* OptionsButton;
  UPROPERTY(meta=(BindWidget))
  UButton* QuitToMainButton;
  UPROPERTY(meta=(BindWidget))
  UButton* QuitToDesktopButton;

  UFUNCTION()
  void Options();
  UFUNCTION()
  void QuitToMainMenu();
  UFUNCTION()
  void QuitToDesktop();
};
