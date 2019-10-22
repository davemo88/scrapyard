// Fill out your copyright notice in the Description page of Project Settings.


#include "BazookaProjectile.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "ScrapyardDamageType.h"
#include "Projectiles/ProjectileAssets.h"
#include "Kismet/GameplayStatics.h"

ABazookaProjectile::ABazookaProjectile()
{
  StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh")); 
  SetRootComponent(StaticMeshComponent);
  SetActorEnableCollision(false);

  ProjectileSpeed = 3000.0f;

  SetReplicates(true);
  SetReplicateMovement(true);

  if (UScrapyardAssets* AssetsBP = UScrapyardGameInstance::AssetsBP)
  {
    OnDestroyParticleSystem = AssetsBP->GetAsset<UParticleSystem>(AssetsBP->DroneAssetsBP->DefaultOnDestroyParticleSystem);
  }

}

void ABazookaProjectile::BeginPlay()
{
  Super::BeginPlay();

  if (HasAuthority())
  {
    PrimaryActorTick.bCanEverTick = true;
    SetActorTickEnabled(true);
    SetLifeSpan(10.0f);
  }

// load assets
  if (!HasAuthority() || GetNetMode() == ENetMode::NM_Standalone)
  {
    if (UScrapyardGameInstance::AssetsBP != nullptr)
    {
      StaticMeshComponent->SetStaticMesh(UScrapyardGameInstance::AssetsBP->GetAsset<UStaticMesh>(UScrapyardGameInstance::AssetsBP->ProjectileAssetsBP->BazookaProjectileMesh));
      StaticMeshComponent->SetMaterial(0, UScrapyardGameInstance::AssetsBP->GetAsset<UMaterial>(UScrapyardGameInstance::AssetsBP->ProjectileAssetsBP->BazookaProjectileMaterial));
    }
  }

}

void ABazookaProjectile::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  FVector NextLocation = GetActorLocation() + (DeltaTime * ProjectileSpeed * FireDirection);
  FHitResult OutHit;
  GetWorld()->SweepSingleByChannel(OutHit, GetActorLocation(), NextLocation, FQuat(), ECollisionChannel::ECC_WorldStatic, FCollisionShape::MakeSphere(50),FCollisionQueryParams());
  DrawDebugSphere(GetWorld(), NextLocation, 50.0f, 10, FColor::Red, false);
  if (OutHit.Actor != NULL)
  {
    UE_LOG(LogTemp,  Warning, TEXT("%s::Hit an Actor %s"), *GetName(), *OutHit.Actor->GetName());
    OutHit.Actor->TakeDamage(
        100.0f,
        FScrapyardPointDamageEvent(
          100.0f,
          OutHit,
          FVector::ZeroVector,
          UScrapyardDamageType::StaticClass(),
          FVector::ZeroVector),
        RobotOwner->Controller,
        this);
    MulticastPlayOnDestroyEffects();
    Destroy();
  }
  else
  {
    SetActorLocation(NextLocation);
  }
}

void ABazookaProjectile::LifeSpanExpired()
{
  UE_LOG(LogTemp,  Warning, TEXT("%s::LifeSpanExpired"), *GetName());
  MulticastPlayOnDestroyEffects();
  Super::LifeSpanExpired();
}

void ABazookaProjectile::BeginDestroy()
{
  Super::BeginDestroy();
}

void ABazookaProjectile::PlayOnDestroyEffects()
{
  UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OnDestroyParticleSystem, GetActorLocation());
}
