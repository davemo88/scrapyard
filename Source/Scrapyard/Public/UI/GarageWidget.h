// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GarageWidget.generated.h"

class USoloDraft;
class UPartCardWidget;
class URobotPart;
class ARobotBodyGarage;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UGarageWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetSoloDraft(USoloDraft* _SoloDraft);

	void SetRobotBodyGarage(ARobotBodyGarage* _RobotBody);

	UFUNCTION(BlueprintCallable)
	void DisplayHeads();
	UFUNCTION(BlueprintCallable)
	void DisplayCores();
	UFUNCTION(BlueprintCallable)
	void DisplayArms();
	UFUNCTION(BlueprintCallable)
	void DisplayLegs();
	UFUNCTION(BlueprintCallable)
	void GotoGarageTestLevel();
	
protected:

	USoloDraft* SoloDraft;

	ARobotBodyGarage* RobotBodyGarage;
	
	void RemovePartCards();

	template <class T>
	void AddPartCards(TArray<T*> Parts);

	UFUNCTION()
	void AssignPart(URobotPart* Part);

};
