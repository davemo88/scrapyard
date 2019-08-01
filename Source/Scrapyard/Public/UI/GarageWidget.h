// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "UI/InstalledPartWidget.h"
#include "Parts/PartAssignment.h"
#include "Parts/RobotPart.h"
#include "Robots/RobotStats.h"
#include "GarageWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPartAssignedDelegate, URobotPart*, RobotPart);

class UYourPartsWidget;
class URobotStatsWidget;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UGarageWidget : public UUserWidget
{
  GENERATED_BODY()

public:

  void SetSoloDraft(USoloDraft* NewSoloDraft);

//TODO: maybe proper methods to modify these?  
  UPROPERTY(meta=(BindWidget))
  URobotStatsWidget* RobotStatsWidget;

  UPROPERTY(meta=(BindWidget))
  UYourPartsWidget* YourPartsWidget;

  UPROPERTY(meta=(BindWidget))
  UButton* RobotTestButton;

  UPROPERTY(meta=(BindWidget))
  UButton* BattleButton;

  UPROPERTY(meta=(BindWidget))
  UInstalledPartWidget* InstalledHeadWidget;

  UPROPERTY(meta=(BindWidget))
  UInstalledPartWidget* InstalledCoreWidget;

  UPROPERTY(meta=(BindWidget))
  UInstalledPartWidget* InstalledArmsWidget;

  UPROPERTY(meta=(BindWidget))
  UInstalledPartWidget* InstalledLegsWidget;

  UPROPERTY(meta=(BindWidget))
  UInstalledPartWidget* InstalledBoosterWidget;

  UPROPERTY(meta=(BindWidget))
  UInstalledPartWidget* InstalledRightHandheldWidget;

  FPartAssignedDelegate PartAssignedDelegate;

protected:

  virtual void NativeConstruct() override;

  USoloDraft* SoloDraft;

  UPROPERTY()
  UPartAssignment* NewValueAssignment;
  UPROPERTY()
  URobotStats* NewValueStats;

  UFUNCTION()
  void OnNewCardReady(UPartCardWidget* CardWidget);

  UFUNCTION()
  void OnCardMouseEntered(URobotPart* RobotPart);
  UFUNCTION()
  void OnCardMouseLeft(URobotPart* RobotPart);

  UFUNCTION()
  void OnCardAssigned(UPartCardWidget* CardWidget);

};
