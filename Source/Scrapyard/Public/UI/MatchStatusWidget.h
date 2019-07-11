// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Animation/WidgetAnimation.h"
#include "MatchStatusWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UMatchStatusWidget : public UUserWidget
{
  GENERATED_BODY()
  
public:

  UFUNCTION()
  void SetAnnouncement(FText AnnouncementText);

  UFUNCTION()
  void StartMatchTimer();
  UFUNCTION()
  void StopMatchTimer();
  UFUNCTION()
  void UpdateMatchTimer();

  UFUNCTION()
  void OnReadyToStartMatch(bool bReady);

  UFUNCTION()
  void ShowScreenBlocker();
  
protected:

  virtual void NativeConstruct() override;

  UPROPERTY(meta=(BindWidget))
  UTextBlock* Announcement;
  
  UPROPERTY(meta=(BindWidget))
  UTextBlock* MatchTime;

  UPROPERTY(meta=(BindWidget))
  UBorder* ScreenBlocker;

  UPROPERTY(meta=(BindWidgetAnim))
  UWidgetAnimation* ScreenBlockerFade;
  
};
