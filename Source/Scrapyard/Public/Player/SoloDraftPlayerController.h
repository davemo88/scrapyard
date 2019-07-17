// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/MenuPlayerController.h"
#include "SoloDraftPlayerController.generated.h"

class USoloDraftWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPartDraftedDelegate, URobotPart*, DraftedPart);
/**
 * 
 */
UCLASS()
class SCRAPYARD_API ASoloDraftPlayerController : public AMenuPlayerController
{
  GENERATED_BODY()

public:

  ASoloDraftPlayerController();

  UFUNCTION()
  void OnNextPack();

  FPartDraftedDelegate PartDraftedDelegate;

//TODO: move to gamestate
  UFUNCTION()
  void OnPartCardHovered(URobotPart* RobotPart);

  UFUNCTION()
  void OnPartDrafted(URobotPart* RobotPart);

protected:

  UPROPERTY()
  USoloDraftWidget* SoloDraftWidget;

  void SetupWidget() override;

};
