// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "UI/RobotTunerWidget.h"
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
  URobotTunerWidget* TunerWidget;

protected:

  virtual void NativeConstruct() override; 
  virtual void NativeOnInitialized() override; 

  UFUNCTION()
  void Options();
  UFUNCTION()
  void QuitToMainMenu();
  UFUNCTION()
  void QuitToDesktop();
  UFUNCTION()
  void ShowTunerWidget();

  UPROPERTY(meta=(BindWidget))
  UButton* OptionsButton;
  UPROPERTY(meta=(BindWidget))
  UButton* QuitToMainMenuButton;
  UPROPERTY(meta=(BindWidget))
  UButton* QuitToDesktopButton;
  UPROPERTY(meta=(BindWidget))
  UButton* TunerWidgetButton;
};
