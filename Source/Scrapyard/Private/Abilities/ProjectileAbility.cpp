// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileAbility.h"
#include "Scrapyard.h"
#include "Targeting/RectangularTargetingProfile.h"
#include "DrawDebugHelpers.h"
#include "Projectiles/BazookaProjectile.h"
#include "Robots/RobotCharacter.h"

AProjectileAbility::AProjectileAbility()
{
  AbilityName = TEXT("Bazooka");
//  AbilityRange = 3000;
//  SetActorTickEnabled(false);
}

void AProjectileAbility::FireShot() 
{
// spawn bazooka projectile
  UE_LOG(LogAbilities,Log,TEXT("%s::FireShot"), *GetName());
  FAbilityEffectParams AbilityEffectParams;
  FHitResult Hit;
  FVector FireDirection;
  const FVector FireLoc = RobotOwner->GetActorLocation() + RobotOwner->RobotBodyComponent->GetComponentRotation().RotateVector(FVector(-70,220,70));

  if (RobotOwner->RobotTargetingComponent->IsTargetAcquired())
  {
    AActor* Target = RobotOwner->RobotTargetingComponent->GetTargets()[0];
    const FVector PredictedLoc = RobotOwner->RobotTargetingComponent->GetPredictedTargetLocation(Target, 0.0f);
    FireDirection = (PredictedLoc - FireLoc).GetSafeNormal();
  }
  else
  {
    FireDirection = RobotOwner->GetViewRotation().Vector(); 
  }
  if (HasAuthority())
  {
    ABazookaProjectile* Bazooka = GetWorld()->SpawnActor<ABazookaProjectile>(FireLoc, FRotator::ZeroRotator, FActorSpawnParameters());
    Bazooka->FireDirection = FireDirection;
    Bazooka->RobotOwner = RobotOwner;
    Bazooka->SetReplicates(true);
  }

}

void AProjectileAbility::SetupTargetingProfile()
{
  TargetingProfile = CreateDefaultSubobject<URectangularTargetingProfile>(TEXT("TargetingProfile"));
}

void AProjectileAbility::ShowAbilityEffects(FAbilityEffectParams AbilityEffectParams)
{

}
