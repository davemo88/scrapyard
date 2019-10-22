// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Robots/RobotCharacter.h"
#include "ScrapyardProjectile.generated.h"

UCLASS()
class SCRAPYARD_API AScrapyardProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScrapyardProjectile();

        UPROPERTY()
        ARobotCharacter* RobotOwner;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

//TODO: why reliable?
        UFUNCTION(NetMulticast, Unreliable)
        void MulticastPlayOnDestroyEffects();

        virtual void PlayOnDestroyEffects();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
