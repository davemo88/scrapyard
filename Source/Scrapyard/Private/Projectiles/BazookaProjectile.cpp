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
  StaticMeshComponent->SetupAttachment(GetRootComponent());

  ProjectileSpeed = 9000.0f;
  ProjectileSize = 50.0f;
  ProjectileLifeSpan = 999.0f;

  if (UScrapyardAssets* AssetsBP = UScrapyardGameInstance::AssetsBP)
  {
    OnDestroyParticleSystem = AssetsBP->GetAsset<UParticleSystem>(AssetsBP->DroneAssetsBP->DefaultOnDestroyParticleSystem);
  }

}

void ABazookaProjectile::BeginPlay()
{
  Super::BeginPlay();

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

void ABazookaProjectile::PlayOnDestroyEffects()
{
  UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OnDestroyParticleSystem, GetActorLocation());
}
