// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"
#include "Scrapyard.h"
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

  CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
  CapsuleComponent->SetCapsuleHalfHeight(50.0f); 
  CapsuleComponent->SetCapsuleRadius(50.0f); 
  SetRootComponent(CapsuleComponent);

  StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

  StaticMeshComponent->SetupAttachment(GetRootComponent());

  StaticMeshComponent->SetRelativeLocation(FVector(0.0f,0.0f,-50.0f));

  if (UScrapyardAssets* AssetsBP = UScrapyardGameInstance::AssetsBP)
  {
    StaticMesh = AssetsBP->DroneAssetsBP->DefaultMesh;
    Material = AssetsBP->DroneAssetsBP->DefaultMaterial;
    OnDestroyParticleSystem = AssetsBP->GetAsset<UParticleSystem>(AssetsBP->DroneAssetsBP->DefaultOnDestroyParticleSystem);
    OnHitParticleSystem = AssetsBP->GetAsset<UParticleSystem>(AssetsBP->DroneAssetsBP->DefaultOnHitParticleSystem);
  }

  HitPoints = 150;

//  OnTakeAnyDamage.AddDynamic(this, &ADrone::OnDroneTakeAnyDamage);

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
  UE_LOG(LogDrone, Verbose, TEXT("%s::TakeDamage - %i damage from %s"), *GetName(), int(DamageAmount), *DamageCauser->GetName());
  HitPoints = FMath::Max(0,HitPoints - int(DamageAmount));

  if (HitPoints == 0)
  {
    SetLifeSpan(0.001f);
  }
  else
  {
    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OnHitParticleSystem, GetActorLocation());
  }

  return DamageAmount;

}

void ADrone::BeginDestroy()
{
  Super::BeginDestroy();
}

void ADrone::LifeSpanExpired()
{
  UE_LOG(LogDrone, Log, TEXT("%s::LifeSpanExpired"), *GetName());
  UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OnDestroyParticleSystem, GetActorLocation());
  TargetableComponent->UnregisterWithGamestate();
//TODO: LifeSpanExpired just calls Destroy. why isn't this being destroyed immediately?
  Super::LifeSpanExpired();
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
  UE_LOG(LogTargeting, Log, TEXT("%s::IsTargetableBy"), *GetName());
  UE_LOG(LogTargeting, Verbose, TEXT("Targetable Team: %i; Robot Team: %i"), Team, Robot->Team);
  return Team != Robot->Team;
}
