// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/ScrapyardPlayerController.h"
#include "RobotPlayerController.generated.h"


UCLASS(config=Game)
class SCRAPYARD_API ARobotPlayerController : public AScrapyardPlayerController
{
	GENERATED_BODY()

public:

	ARobotPlayerController();
};
