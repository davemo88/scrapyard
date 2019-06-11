// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "Robots/RobotCharacter.h"
#include "Kismet/GameplayStatics.h"


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
    OnDestroyParticleSystem = AssetsBP->GetAsset<UParticleSystem>(AssetsBP->DroneAssetsBP->DefaultOnDestroyParticleSystem);
  }

  HitPoints = 100;

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

float ADrone::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::TakeDamage - %i damage from %s"), *GetName(), int(DamageAmount), *DamageCauser->GetName());
  HitPoints = FMath::Max(0,HitPoints - int(DamageAmount));

  if (HitPoints == 0)
  {
    UE_LOG(LogTemp, Warning, TEXT("Drone Destroyed"));
    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OnDestroyParticleSystem, GetActorLocation());
    Destroy();
  }

  return Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);

}

void ADrone::BeginDestroy()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginDestroy"), *GetName());

  Super::BeginDestroy();

}

void ADrone::SetAssets()
{
  if (UScrapyardAssets* AssetsBP = UScrapyardGameInstance::AssetsBP)
  {
    StaticMeshComponent->SetStaticMesh(AssetsBP->GetAsset<UStaticMesh>(StaticMesh));
    StaticMeshComponent->SetMaterial(0,AssetsBP->GetAsset<UMaterial>(Material));
  }
}

bool ADrone::IsTargetableBy(ARobotCharacter* Robot)
{
  return Team != Robot->Team;
}
