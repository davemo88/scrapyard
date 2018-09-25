// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"
#include "RobotPart.h"
#include "RobotPartCardActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRobotPartCardClickedEvent, URobotPart*, RobotPart);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRobotPartCardClickedEvent, TSubclassOf<URobotPart>, RobotPart);

UCLASS()
class SCRAPYARD_API ARobotPartCardActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARobotPartCardActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//	void SetRobotPart(URobotPart* NewRobotPart);
	void SetRobotPart(TSubclassOf<URobotPart> NewRobotPart);

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* CardTitleComponent;

	UPROPERTY(EditAnywhere)
	UBoxComponent* ClickableComponent;
	
	UFUNCTION()
	void DoOnClicked(AActor *Target, FKey ButtonPressed);

	UPROPERTY()
	FRobotPartCardClickedEvent OnRobotPartCardClicked;

	UPROPERTY(EditAnywhere)
	URobotPart* RobotPart;
	
};
