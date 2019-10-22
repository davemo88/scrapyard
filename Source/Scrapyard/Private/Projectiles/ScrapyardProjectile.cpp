// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrapyardProjectile.h"


// Sets default values
AScrapyardProjectile::AScrapyardProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AScrapyardProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScrapyardProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AScrapyardProjectile::MulticastPlayOnDestroyEffects_Implementation()
{
  UE_LOG(LogTemp,  Warning, TEXT("%s::MulticastPlayOnDestroyEffects_Implementation"), *GetName());
  if (!HasAuthority() || GetNetMode() == ENetMode::NM_Standalone)
  {
    PlayOnDestroyEffects(); 
  }
}

void AScrapyardProjectile::PlayOnDestroyEffects()
{

}
