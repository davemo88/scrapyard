// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RobotHUDWidget.generated.h"

class ARobotCharacter;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API URobotHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetRobotCharacter(ARobotCharacter* _RobotCharacter);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetPowerPercent();
	
protected:

	ARobotCharacter* RobotCharacter;
	
};
