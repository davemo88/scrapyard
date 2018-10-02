// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"
#include "RobotPart.h"
#include "RobotPartActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRobotPartClickedEvent, URobotPart*, RobotPart);

UCLASS()
class SCRAPYARD_API ARobotPartActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARobotPartActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:


public:	
//	void SetRobotPart(URobotPart* NewRobotPart);
	void SetRobotPart(TSubclassOf<URobotPart> NewRobotPart);

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* TextComponent;

	UPROPERTY(EditAnywhere)
	UBoxComponent* ClickableComponent;
	
	UFUNCTION()
	void DoOnClicked(AActor *Target, FKey ButtonPressed);

	UPROPERTY()
	FRobotPartClickedEvent OnRobotPartClicked;

	UPROPERTY(EditAnywhere)
	URobotPart* RobotPart;
	
};
