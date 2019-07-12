// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserProjectile.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "Projectiles/ProjectileAssets.h"

ALaserProjectile::ALaserProjectile()
{
  LaserBeam = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LaserBeam"));
  
  if (UScrapyardGameInstance::AssetsBP != nullptr)
  {
    UE_LOG(LogTemp, Warning, TEXT("setting beam"));
    LaserBeam->SetTemplate(UScrapyardGameInstance::AssetsBP->GetAsset<UParticleSystem>(UScrapyardGameInstance::AssetsBP->ProjectileAssetsBP->LaserBeamParticleSystem));
  }
}

