// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPlayerController.generated.h"

class UMainMenuWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWidgetReadyDelegate);

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AMenuPlayerController : public APlayerController
{
  GENERATED_BODY()

public:
  AMenuPlayerController();

  void PostInitializeComponents() override;

  void BeginPlay() override;

  UPROPERTY()
  UUserWidget* Widget;

  virtual void SetupWidget() {};

  FOnWidgetReadyDelegate OnWidgetReadyDelegate;
};
