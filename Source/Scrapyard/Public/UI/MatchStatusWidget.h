// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
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
  
protected:

  virtual void NativeConstruct() override;

  UPROPERTY(meta=(BindWidget))
  UTextBlock* Announcement;
  
  UPROPERTY(meta=(BindWidget))
  UTextBlock* MatchTime;
  
};
