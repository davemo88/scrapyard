// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "Robots/RobotCharacter.h"


// Sets default values
ADrone::ADrone()
{
   // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  TargetableComponent = CreateDefaultSubobject<UTargetableComponent>(TEXT("TargetableComponent"));

  StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

  if (UScrapyardAssets* AssetsBP = UScrapyardGameInstance::AssetsBP)
  {
    StaticMesh = AssetsBP->DroneAssetsBP->DefaultMesh;
    Material = AssetsBP->DroneAssetsBP->DefaultMaterial;
  }

}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
  Super::BeginPlay();

  SetAssets();
  
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

void ADrone::SetAssets()
{
  if (UScrapyardAssets* AssetsBP = UScrapyardGameInstance::AssetsBP)
  {
    StaticMeshComponent->SetStaticMesh(AssetsBP->GetAsset<UStaticMesh>(StaticMesh));
    StaticMeshComponent->SetMaterial(0,AssetsBP->GetAsset<UMaterial>(Material));
  }
}
