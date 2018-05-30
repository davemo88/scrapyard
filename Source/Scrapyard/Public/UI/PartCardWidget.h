// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PartCardWidget.generated.h"

class URobotPart;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UPartCardWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetRobotPart(URobotPart* RobotPart);

	UPROPERTY(BlueprintReadonly)
	URobotPart* RobotPart;

};
