// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"
#include "Robots/RobotCharacter.h"


// Sets default values
ADrone::ADrone()
{
   // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  TargetableComponent = CreateDefaultSubobject<UTargetableComponent>(TEXT("TargetableComponent"));

  StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
  Super::BeginPlay();
  
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

}

bool ADrone::IsTargetableBy(ARobotCharacter* Robot)
{
  return Team != Robot->Team;
}
