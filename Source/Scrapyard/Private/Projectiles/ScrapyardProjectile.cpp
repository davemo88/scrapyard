// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrapyardProjectile.h"


// Sets default values
AScrapyardProjectile::AScrapyardProjectile()
{
   // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  SetReplicates(true);
  SetReplicateMovement(true);

  SetActorEnableCollision(false);

  CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
  SetRootComponent(CapsuleComponent);
  CapsuleComponent->SetSimulatePhysics(true);
  CapsuleComponent->SetEnableGravity(false);
//  ProjectileMovementComponent->SetUpdatedComponent(GetRootComponent());

//  ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

// Called when the game starts or when spawned
void AScrapyardProjectile::BeginPlay()
{
  Super::BeginPlay();

  if (HasAuthority())
  {
    SetActorTickEnabled(true);
    SetLifeSpan(ProjectileLifeSpan);
  }
  else
  {
    SetActorTickEnabled(false);
  }
}

// Called every frame
void AScrapyardProjectile::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}

void AScrapyardProjectile::Fire(FVector FireDirection)
{
  UE_LOG(LogTemp,  Warning, TEXT("%s::Fire"), *GetName());
  UE_LOG(LogTemp,  Warning, TEXT("FireDirection - %s ProjectileSpeed - %f"), *FireDirection.ToString(), ProjectileSpeed);
  CapsuleComponent->SetPhysicsLinearVelocity(FireDirection * ProjectileSpeed, false);
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
