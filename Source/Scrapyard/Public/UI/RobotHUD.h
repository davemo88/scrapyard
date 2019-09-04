// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RobotHUD.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API ARobotHUD : public AHUD
{
  GENERATED_BODY()

public:

  ARobotHUD();
  
  virtual void DrawHUD() override;

protected:

  virtual void DrawTargetBox(AActor* Target);
  
  virtual FLinearColor GetTargetingColor();

  virtual void DrawControlRectangle();

  virtual void DrawControlEllipse();

  virtual float GetControlEllipseRadius(float theta, float a, float b);

  virtual void DrawTargetingSystem();
  
};
