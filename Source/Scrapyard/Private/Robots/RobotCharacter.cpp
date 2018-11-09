// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotCharacter.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/RobotGameMode.h"
#include "Robots/RobotMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Ability/HitscanAbility.h"

// Sets default values
ARobotCharacter::ARobotCharacter(const class FObjectInitializer& ObjectInitializer)
//  : Super(ObjectInitializer)
  : Super(ObjectInitializer.SetDefaultSubobjectClass<URobotMovementComponent>(ARobotCharacter::CharacterMovementComponentName))
{
   // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  bReplicates = true;
  bAlwaysRelevant = true;
// maybe we need to put the default subobjects in the constructor?
  SetupCamera();
  SetupBody();
  SetupStats();

  SetupAbilities();

// allow flying movement
// why is this here as well as the movement component in the initializer list
  UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetCharacterMovement());

}

// Called when the game starts or when spawned
void ARobotCharacter::BeginPlay()
{
  Super::BeginPlay();

}

// Called every frame
void ARobotCharacter::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARobotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);
  /* Movement */
//  PlayerInputComponent->BindAxis("MoveX", this, &ARobotCharacter::Axis_MoveX);
//  PlayerInputComponent->BindAxis("MoveY", this, &ARobotCharacter::Axis_MoveY);
//
//  PlayerInputComponent->BindAxis("TurnZ", this, &APawn::AddControllerYawInput);
//  PlayerInputComponent->BindAxis("TurnY", this, &APawn::AddControllerPitchInput);
//
//  PlayerInputComponent->BindAxis("Boost", this, &ARobotCharacter::Axis_Boost);
//
//  PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARobotCharacter::Jump);

//  PlayerInputComponent->BindAction("PrimaryFire", IE_Pressed, this, &ARobotCharacter::StartFire);
}

void ARobotCharacter::SetupCamera()
{
  RootComponent = GetRootComponent();

  CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
  CameraBoom->SetupAttachment(RootComponent);

  CameraBoom->bAbsoluteRotation = false;
  CameraBoom->TargetArmLength = 300.f;
  CameraBoom->SocketOffset = FVector(0.f, 0.f, 50.f);
  CameraBoom->bUsePawnControlRotation = true;
  
  OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));

  OurCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

void ARobotCharacter::SetupBody()
{
  RobotBodyComponent = CreateDefaultSubobject<URobotBodyComponent>(TEXT("RobotBodyComponent"));

  RootComponent = GetRootComponent();
  RobotBodyComponent->SetupAttachment(RootComponent);
// TODO: why do i have to make these weird adjustments?
  RobotBodyComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -88.f));
  RobotBodyComponent->SetRelativeRotation(FRotator(0.0f,-90.0f,0.f));
}

void ARobotCharacter::SetupStats()
{
  RobotStats = CreateDefaultSubobject<URobotStats>(TEXT("RobotStats"));
  RobotStats->RobotStatsUpdatedDelegate.AddDynamic(this, &ARobotCharacter::OnStatsUpdated);
  RobotStats->SetPartAssignment(RobotBodyComponent->PartAssignment);
}

void ARobotCharacter::SetupAbilities()
{
//  UE_LOG(LogTemp, Warning, TEXT("ARobotCharacter::SetupAbilities"));
//  if (RobotBodyComponent && RobotBodyComponent->RightHandheld && RobotBodyComponent->RightHandheld->PartAbililty)
//  {
//    WeaponAbility = RobotBodyComponent->RightHandheld->PartAbililty;
//  }
  if (WeaponAbility == NULL)
  {
    UE_LOG(LogTemp, Warning, TEXT("Couldn't set up Weapon Ability from part, doing it directly :(" ));
    WeaponAbility = CreateDefaultSubobject<AHitscanAbility>(TEXT("WeaponAbility"));
    WeaponAbility->RobotOwner = this;
  }
}

void ARobotCharacter::OnStatsUpdated()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnStatsUpdated"), *GetName());
  HitPoints = RobotStats->HitPoints;
  UE_LOG(LogTemp, Warning, TEXT("Power: %i"), RobotStats->MaxPower);
  Power = RobotStats->MaxPower;
}

void ARobotCharacter::Axis_MoveX(float AxisValue)
{
  if (Controller && AxisValue != 0.f)
  {
    // Limit pitch when walking or falling
    URobotMovementComponent* MovementComponent = Cast<URobotMovementComponent>(GetMovementComponent());
    const bool bLimitRotation = (MovementComponent->IsMovingOnGround() || MovementComponent->IsFalling() || MovementComponent->IsFlying());
//    const bool bLimitRotation = (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling());
    const FRotator Rotation = bLimitRotation ? GetActorRotation() : Controller->GetControlRotation();
    const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

    AddMovementInput(Direction, AxisValue);
  }
}

void ARobotCharacter::Axis_MoveY(float AxisValue)
{
  if (AxisValue != 0.f)
  {
    const FRotator Rotation = GetActorRotation();
    const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
    AddMovementInput(Direction, AxisValue);
  }
}

void ARobotCharacter::Axis_Boost(float AxisValue)
{
  URobotMovementComponent* MovementComponent = Cast<URobotMovementComponent>(GetMovementComponent());
  FString MovementModeName = MovementComponent->GetMovementName();
//  UE_LOG(LogTemp, Warning, TEXT("Preboost Movement Mode: %s "), *MovementModeName);
  if (AxisValue != 0.f && Power > 0)
  {
    Power = FMath::Max(Power - (int)(RobotStats->BoosterPowerDrain * AxisValue * 0.1), 0);
    if (MovementComponent->IsWalking())
    {

    }
    else if (MovementComponent->IsFalling())
    {
      {
        MovementComponent->SetMovementMode(MOVE_Flying, 5);
      }
    }
    else if (MovementComponent->IsFlying())
    {
      const FVector Up = FVector(0, 0, 1);
      AddMovementInput(Up, AxisValue);
    }
  }
  else if (AxisValue != 0.f && Power <= 0)
  {
    if (MovementComponent->IsFlying())
    {
      {
        MovementComponent->SetMovementMode(MOVE_Falling, 5);
      }
    }
  }
  else if (AxisValue == 0.f)
  {
    if (Power < RobotStats->MaxPower)
    {
      Power = Power + 10;
    }

    if (MovementComponent->IsFlying())
    {
      MovementComponent->SetMovementMode(MOVE_Falling, 3);
    }
  };
//  UE_LOG(LogTemp, Warning, TEXT("Postboost Movement Mode: %s "), *MovementModeName);

// better to switch on this enum type later
//  EMovementMode MovementMode = MovementComponent->MovementMode;
}

//void ARobotCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
//{
//    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//}
//

float ARobotCharacter::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
  UE_LOG(LogTemp, Warning, TEXT("ARobotCharacter::TakeDamage"));

  // CDO = class default object
  const UDamageType* const DamageTypeCDO = DamageEvent.DamageTypeClass ? DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>() : GetDefault<UDamageType>();

  const UScrapyardDamageType* const ScrapyardDamageTypeCDO = Cast<UScrapyardDamageType>(DamageTypeCDO);
  
  int32 IntDamage = FMath::TruncToInt(Damage);

//  ARobotPlayerState* RobotPlayerState = Cast<ARobotPlayerState>(PlayerState);

  FHitResult HitInfo;
  {
    FVector SomeVector;
    DamageEvent.GetBestHitInfo(this, DamageCauser, HitInfo, SomeVector);
  }

  ARobotGameMode* GameMode = GetWorld()->GetAuthGameMode<ARobotGameMode>();

  DrawDebugString(GetWorld(), HitInfo.Location, FString::FromInt(IntDamage), nullptr, FColor::Red, 10.f, true);
  
  return 0.0f;
}

void ARobotCharacter::StartFire(uint8 FireModeNum)
{
  UE_LOG(LogTemp,Warning,TEXT("ARobotCharacter::StartFire"));

  if (!IsLocallyControlled())
  {
    UE_LOG(LogTemp, Warning, TEXT("StartFire can only be called on the owning client"));
  }
  else
  {
    if (WeaponAbility != NULL)
    {
      WeaponAbility->StartFire(FireModeNum);
    }
    else
    {
      UE_LOG(LogTemp, Warning, TEXT("ARobotCharacter::WeaponAbility is NULL"));
    }
  }
}

void ARobotCharacter::StopFire(uint8 FireModeNum)
{
  UE_LOG(LogTemp,Warning,TEXT("ARobotCharacter::StopFire"));
  if (WeaponAbility != NULL)
  {
    WeaponAbility->StopFire(FireModeNum);
  }
  else
  {
    SetPendingFire(FireModeNum, false); 
  }
}

void ARobotCharacter::StopFiring()
{
  for (int32 i = 0; i < PendingFire.Num(); i++)
  {
    if (PendingFire[i])
    {
      StopFire(i);
    }
  }
}
