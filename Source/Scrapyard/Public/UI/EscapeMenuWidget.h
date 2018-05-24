// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EscapeMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UEscapeMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Options();
	UFUNCTION(BlueprintCallable)
	void QuitToMainMenu();
	UFUNCTION(BlueprintCallable)
	void QuitToDesktop();
};
