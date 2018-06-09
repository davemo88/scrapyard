// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotBodyGarage.h"


// Sets default values
ARobotBodyGarage::ARobotBodyGarage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RobotBodyComponent = CreateDefaultSubobject<URobotBodyComponent>(TEXT("RobotBodyComponent"));
//	RootComponent = GetRootComponent();
//	RobotBodyComponent->SetupAttachment(RootComponent);

	RobotBodyComponent->SetEnableGravity(false);
}

// Called when the game starts or when spawned
void ARobotBodyGarage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARobotBodyGarage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

