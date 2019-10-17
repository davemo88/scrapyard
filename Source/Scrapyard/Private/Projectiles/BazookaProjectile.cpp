// Fill out your copyright notice in the Description page of Project Settings.


#include "BazookaProjectile.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "Projectiles/ProjectileAssets.h"

ABazookaProjectile::ABazookaProjectile()
{
  StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh")); 
}

void ABazookaProjectile::BeginPlay()
{
  if (!HasAuthority())
  {
    if (UScrapyardGameInstance::AssetsBP != nullptr)
    {
      StaticMesh->SetStaticMesh(UScrapyardGameInstance::AssetsBP->GetAsset<UStaticMesh>(UScrapyardGameInstance::AssetsBP->ProjectileAssetsBP->BazookaProjectileMesh));
    }
  }
}

void ABazookaProjectile::Tick(float DeltaTime)
{

}



