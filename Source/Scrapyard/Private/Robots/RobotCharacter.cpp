// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotCharacter.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/RobotGameMode.h"
#include "Robots/RobotMovementComponent.h"
#include "Game/RobotGameState.h"
#include "Player/RobotPlayerController.h"
#include "Player/RobotPlayerState.h"
#include "Game/ScrapyardDefaultAssets.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/HUD.h"
#include "Abilities/HitscanAbility.h"
#include "UI/RobotHUDWidget.h"
#include "Blueprint/UserWidget.h"
#include "DrawDebugHelpers.h"
#include "UnrealNetwork.h"
#include "Math/UnrealMathVectorConstants.h"
#include "Engine.h"

// Sets default values
ARobotCharacter::ARobotCharacter(const class FObjectInitializer& ObjectInitializer)
//  : Super(ObjectInitializer)
  : Super(ObjectInitializer.SetDefaultSubobjectClass<URobotMovementComponent>(ARobotCharacter::CharacterMovementComponentName))
{
  UE_LOG(LogTemp, Warning, TEXT("%s::ARobotCharacter"), *GetName());
   // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  bReplicates = true;
  bAlwaysRelevant = true;

  SetupCamera();
  SetupBody();
  SetupStats();

// allow flying movement
// why is this here as well as the movement component in the initializer list
  UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetCharacterMovement());

  RobotTargetingComponent = CreateDefaultSubobject<URobotTargetingComponent>(TEXT("RobotTargetingComponent")); 
  RobotTargetingComponent->SetupAttachment(RootComponent);

// NOTE: maybe sloppy but also seems to make sense
  AddTickPrerequisiteComponent(RobotTargetingComponent);

}

// Called when the game starts or when spawned
void ARobotCharacter::BeginPlay()
{
  Super::BeginPlay();
  const UEnum* NetRoleEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ENetRole"));
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay - Role: %s"), *GetName(), *(NetRoleEnum ? NetRoleEnum->GetNameStringByIndex(Role) : TEXT("oops")));
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay - RemoteRole: %s"), *GetName(), *(NetRoleEnum ? NetRoleEnum->GetNameStringByIndex(GetRemoteRole()) : TEXT("oops")));

  if (ARobotPlayerController* PC = Cast<ARobotPlayerController>(GetController()))
  {
    UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay - PC ok"), *GetName());
    PC->SetRobotCharacter(this);
    if (IsLocallyControlled())
    {
      SetupRobotHUDWidget();
    }
  }

  if (ARobotGameState* RobotGameState = GetWorld()->GetGameState<ARobotGameState>())
  {

    if (HasAuthority())
    {

      for (AActor* Actor: RobotGameState->TargetableActors)
      {
        if (RobotTargetingComponent->IsTargetable(Actor))
        {
          RobotTargetingComponent->AddTargetable(Actor);
        }
      }

      RobotGameState->AddTargetable(this);

      RobotGameState->OnTargetableAddedDelegate.AddDynamic(this, &ARobotCharacter::OnTargetableAdded);
      RobotGameState->OnTargetableRemovedDelegate.AddDynamic(this, &ARobotCharacter::OnTargetableRemoved);
    }
  }
}

void ARobotCharacter::PostInitializeComponents()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::PostInitializeComponents"), *GetName());
  Super::PostInitializeComponents();

  if (HasAuthority())
  {
    SetupAbilities();
  }

  if (URobotMovementComponent* MovementComponent = Cast<URobotMovementComponent>(GetMovementComponent()))
  {
    MovementComponent->SetRobotChar(this);
  }
}

// Called every frame
void ARobotCharacter::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if (HasAuthority())
  {
    bTargetAcquired = RobotTargetingComponent->IsTargetAcquired();
  }


}

// Called to bind functionality to input
void ARobotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetupPlayerInputComponent"), *GetName());

  Super::SetupPlayerInputComponent(PlayerInputComponent);

  ARobotPlayerController* PC = Cast<ARobotPlayerController>(GetController());
//TODO: why this check?
  if (PC)
  {
    InputComponent->BindAxis("MoveX", this, &ARobotCharacter::Axis_MoveX);
    InputComponent->BindAxis("MoveY", this, &ARobotCharacter::Axis_MoveY);

    InputComponent->BindAxis("TurnZ", this, &ARobotCharacter::Axis_TurnZ); //&APawn::AddControllerYawInput);
    InputComponent->BindAxis("TurnY", this, &ARobotCharacter::Axis_TurnY); //&APawn::AddControllerPitchInput);

    InputComponent->BindAction("Boost", IE_Pressed, this, &ARobotCharacter::StartBoosting);
    InputComponent->BindAction("Boost", IE_Released, this, &ARobotCharacter::StopBoosting);

    InputComponent->BindAction("PrimaryFire", IE_Pressed, PC, &ARobotPlayerController::OnFire);
    InputComponent->BindAction("PrimaryFire", IE_Released, PC, &ARobotPlayerController::OnStopFire);
  }
}

void ARobotCharacter::SetupRobotHUDWidget()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetupRobotHUDWidget"), *GetName());
  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
  ARobotPlayerController* PC = Cast<ARobotPlayerController>(GetController());
// TODO: can there be a locally controlled PC with ROLE_Authority? i guess if everything is local?
//  if (Role < ROLE_Authority && PC && IsLocallyControlled())
  if (PC && IsLocallyControlled())
  {
// TODO: perhaps refactor creation of the widget so the widget itself doesn't have to be public
// e.g. use friend class or write a function
    UE_LOG(LogTemp, Warning, TEXT("%s::SetupRobotHUDWidget - local PC"), *GetName());
    PC->RobotHUDWidget = CreateWidget<URobotHUDWidget>(PC, GameInstance->DefaultAssetsBP->RobotHUDWidgetBP);
    PC->RobotHUDWidget->SetRobotCharacter(this);
    PC->RobotHUDWidget->AddToViewport();

    PC->EscapeMenuWidget->TunerWidget->SetRobotChar(this);

//    PC->RobotHUDWidget->SetTargetingWidget(CreateWidget<UTargetingWidget>(PC, GameInstance->DefaultAssetsBP->TargetingWidgetBP));

  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("%s::SetupRobotHUDWidget - nonlocal or null PC"), *GetName());
  }
}

void ARobotCharacter::SetupCamera()
{
  RootComponent = GetRootComponent();

  CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
  CameraBoom->SetupAttachment(RootComponent);

  CameraBoom->bAbsoluteRotation = false;
  CameraBoom->TargetArmLength = 350.f;
  CameraBoom->SocketOffset = FVector(0.f, 0.f, 130.f);
  CameraBoom->bUsePawnControlRotation = true;
  
  OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));

  OurCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

void ARobotCharacter::SetupBody()
{
  RobotBodyComponent = CreateDefaultSubobject<URobotBodyComponent>(TEXT("RobotBodyComponent"));
  RootComponent = GetRootComponent();
  RobotBodyComponent->SetupAttachment(RootComponent);
// this is adjustment for capsule half height i believe
  RobotBodyComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -88.f));
// rotation ?
// seems like the sketetal mesh is not set up correctly
  RobotBodyComponent->SetRelativeRotation(FRotator(0.0f,-90.0f,0.f));
  RobotBodyComponent->PartAssignment->SetDefaultAssignment();
}

void ARobotCharacter::SetupStats()
{
  RobotStats = CreateDefaultSubobject<URobotStats>(TEXT("RobotStats"));
  RobotStats->RobotStatsUpdatedDelegate.AddDynamic(this, &ARobotCharacter::OnStatsUpdated);
  RobotStats->SetPartAssignment(RobotBodyComponent->PartAssignment);
}

void ARobotCharacter::SetupAbilities()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetupAbilities"), *GetName());
//  if (RobotBodyComponent && RobotBodyComponent->RightHandheld && RobotBodyComponent->RightHandheld->PartAbililty)
//  {
//    WeaponAbility = RobotBodyComponent->RightHandheld->PartAbililty;
//  }
  const UEnum* NetRoleEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ENetRole"));
  UE_LOG(LogTemp, Warning, TEXT("%s::SetupAbilities - Role: %s"), *GetName(), *(NetRoleEnum ? NetRoleEnum->GetNameStringByIndex(Role) : TEXT("oops")));
  UE_LOG(LogTemp, Warning, TEXT("%s::SetupAbilities - RemoteRole: %s"), *GetName(), *(NetRoleEnum ? NetRoleEnum->GetNameStringByIndex(GetRemoteRole()) : TEXT("oops")));
  RobotBodyComponent->WeaponAbilityComponent->CreateChildActor();

  WeaponAbility = Cast<AScrapyardAbility>(RobotBodyComponent->WeaponAbilityComponent->GetChildActor());

// TODO: why do we have RobotOwner if we can just the real Owner?
// TODO: why setting owner in two different ways here? seems just wrong
// BUG: should only set owner on the server
  WeaponAbility->RobotOwner = this;
  if (WeaponAbility->GetOwner())
  {
    UE_LOG(LogTemp, Warning, TEXT("%s::SetupAbilities - WeaponAbility Owner: %s"), *GetName(), *WeaponAbility->GetOwner()->GetName());
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("%s::SetupAbilities - WeaponAbility Owner: NULL"), *GetName());
  }
  WeaponAbility->SetOwner(this);
  UE_LOG(LogTemp ,Warning, TEXT("Weapon Ability Replication: %s"), (WeaponAbility->GetIsReplicated() ? TEXT("True") : TEXT("False")));

}

void ARobotCharacter::OnStatsUpdated()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnStatsUpdated"), *GetName());
  UE_LOG(LogTemp, Warning, TEXT("HitPoints: %i"), RobotStats->HitPoints);
  UE_LOG(LogTemp, Warning, TEXT("Power: %i"), RobotStats->MaxPower);

//TODO: functions to do these
//TODO: why aren't these updated on replication?
  HitPoints = RobotStats->HitPoints;
  HitPointsChangedDelegate.Broadcast();
  Power = RobotStats->MaxPower;
  PowerChangedDelegate.Broadcast();
}

void ARobotCharacter::Axis_MoveX(float AxisValue)
{
//TODO: remove this check
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

void ARobotCharacter::Axis_TurnZ(float AxisValue)
{
//  float realtimeSeconds = UGameplayStatics::GetRealTimeSeconds(GetWorld());
//  UE_LOG(LogTemp, Warning, TEXT("ARobotCharacter::Axis_TurnZ - value: %f time: %f"), AxisValue, realtimeSeconds);

//  ARobotPlayerController* PC = Cast<ARobotPlayerController>(GetController());
//  if (PC)
//  {
//    float MouseX;
//    float MouseY;
//    PC->GetMousePosition(MouseX, MouseY);
//
//    MouseX = FMath::Clamp(MouseX, 0.0f, float(GSystemResolution.ResX));
//    MouseY = FMath::Clamp(MouseY, 0.0f, float(GSystemResolution.ResY));
//
////    UE_LOG(LogTemp, Warning, TEXT("mouse position: %fx %fy"), MouseX, MouseY);
//
////    uint32 MaxX = GSystemResolution.ResX;
//    uint32 CenterX = GSystemResolution.ResX / 2;
//
////    UE_LOG(LogTemp, Warning, TEXT("Center X: %i"), CenterX);
//
//    float TurnRate = float(MouseX - CenterX) / float(CenterX);
//
//    float MaxTurnRate = 1.0f;
//
////    UE_LOG(LogTemp, Warning, TEXT("TurnZ Rate: %f"), TurnRate);
//
//    AddControllerYawInput(TurnRate * MaxTurnRate);
//
////    float MaxTargetingAngle = 45.0f;
////
////    RobotTargetingComponent->SetRelativeRotation(FRotator(0.0f,TurnRate * MaxTargetingAngle,0.0f));
//
//  }

  AddControllerYawInput(AxisValue);
}

void ARobotCharacter::Axis_TurnY(float AxisValue)
{
//  float realtimeSeconds = UGameplayStatics::GetRealTimeSeconds(GetWorld());
////  UE_LOG(LogTemp, Warning, TEXT("ARobotCharacter::Axis_TurnY - value: %f time: %f"), AxisValue, realtimeSeconds);
//  ARobotPlayerController* PC = Cast<ARobotPlayerController>(GetController());
//  if (PC)
//  {
//    float MouseX;
//    float MouseY;
//    PC->GetMousePosition(MouseX, MouseY);
//
//    MouseX = FMath::Clamp(MouseX, 0.0f, float(GSystemResolution.ResX));
//    MouseY = FMath::Clamp(MouseY, 0.0f, float(GSystemResolution.ResY));
////    UE_LOG(LogTemp, Warning, TEXT("mouse position: %fx %fy"), MouseX, MouseY);
//
//    uint32 CenterY = GSystemResolution.ResY / 2;
//
////    UE_LOG(LogTemp, Warning, TEXT("Center Y: %i"), CenterY);
//
//    float TurnRate = float(MouseY - CenterY) / float(CenterY);
//
//    float MaxTurnRate = 1.0f;
//
////    UE_LOG(LogTemp, Warning, TEXT("TurnY rate: %f"), TurnRate);
//
//    AddControllerPitchInput(TurnRate * MaxTurnRate);
//  }

  AddControllerPitchInput(AxisValue);
}

//void ARobotCharacter::Axis_Boost(float AxisValue)
//{
//  URobotMovementComponent* MovementComponent = Cast<URobotMovementComponent>(GetMovementComponent());
//  FString MovementModeName = MovementComponent->GetMovementName();
////  UE_LOG(LogTemp, Warning, TEXT("Preboost Movement Mode: %s "), *MovementModeName);
//  if (AxisValue != 0.f && Power > 0)
//  {
//    if (MovementComponent->IsWalking())
//    {
//
//    }
//    else if (MovementComponent->IsFalling())
//    {
//      {
//        MovementComponent->SetMovementMode(MOVE_Flying, 5);
//      }
//    }
//    else if (MovementComponent->IsFlying())
//    {
//// TODO: set some scaling constants for booster thrust and powerdrain
//      const FVector Up = FVector(0, 0, 1);
//      AddMovementInput(Up, AxisValue);
//      Power = FMath::Max(Power - (int)(RobotStats->BoosterPowerDrain * AxisValue * 0.1), 0);
//    }
//  }
//  else if (AxisValue != 0.f && Power <= 0)
//  {
//    if (MovementComponent->IsFlying())
//    {
//      {
//        MovementComponent->SetMovementMode(MOVE_Falling, 5);
//      }
//    }
//  }
//  else if (AxisValue == 0.f)
//  {
//    if (Power < RobotStats->MaxPower)
//    {
//      Power = FMath::Min(RobotStats->MaxPower, Power + 10);
//    }
//
//    if (MovementComponent->IsFlying())
//    {
//      MovementComponent->SetMovementMode(MOVE_Falling, 3);
//    }
//  };
//  if (!HasAuthority())
//  {
//    ServerBoost(AxisValue);
//  }
////  UE_LOG(LogTemp, Warning, TEXT("Postboost Movement Mode: %s "), *MovementModeName);
//
//// better to switch on this enum type later
////  EMovementMode MovementMode = MovementComponent->MovementMode;
//}

void ARobotCharacter::StartBoosting()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::StartBoosting"), *GetName());
  URobotMovementComponent* MoveComp = Cast<URobotMovementComponent>(GetCharacterMovement());
  if (MoveComp)
  {
    MoveComp->SetBoostInput(1);
  }
}

void ARobotCharacter::StopBoosting()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::StopBoosting"), *GetName());
  URobotMovementComponent* MoveComp = Cast<URobotMovementComponent>(GetCharacterMovement());
  if (MoveComp)
  {
    MoveComp->SetBoostInput(0);  
  }
}

//bool ARobotCharacter::ServerBoost_Validate(float AxisValue)
//{
//  return true;
//}
//
//void ARobotCharacter::ServerBoost_Implementation(float AxisValue)
//{
//  Axis_Boost(AxisValue);
//}

float ARobotCharacter::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
  UE_LOG(LogTemp, Warning, TEXT("ARobotCharacter::TakeDamage"));

  // CDO = class default object
  const UDamageType* const DamageTypeCDO = DamageEvent.DamageTypeClass ? DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>() : GetDefault<UDamageType>();

  const UScrapyardDamageType* const ScrapyardDamageTypeCDO = Cast<UScrapyardDamageType>(DamageTypeCDO);

  FHitResult HitInfo;
  {
    FVector SomeVector;
    DamageEvent.GetBestHitInfo(this, DamageCauser, HitInfo, SomeVector);
  }

  if (HasAuthority())
  {
    MulticastShowDamage(Damage, DamageEvent, EventInstigator, DamageCauser, HitInfo);
    HitPoints = FMath::Max(0,HitPoints-(int)Damage);
    UE_LOG(LogTemp, Warning, TEXT("%s::TakeDamage - HitPoints set to %d"), *GetName(), HitPoints);

    if (HitPoints == 0)
    {
      ZeroHitPointsDelegate.Broadcast();
    }
  }

  return Damage;
}

void ARobotCharacter::MulticastShowDamage_Implementation(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser, FHitResult HitInfo)
{
  int32 IntDamage = FMath::TruncToInt(Damage);
  DrawDebugString(GetWorld(), HitInfo.Location, FString::FromInt(IntDamage), nullptr, FColor::Red, 10.f, true);
}

void ARobotCharacter::StartFire(uint8 FireModeNum)
{
  UE_LOG(LogTemp,Warning,TEXT("%s::StartFire"), *GetName());

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

void ARobotCharacter::GetLifetimeReplicatedProps(TArray <FLifetimeProperty > & OutLifetimeProps) const
{
  Super::GetLifetimeReplicatedProps(OutLifetimeProps);

  DOREPLIFETIME(ARobotCharacter, WeaponAbility);
  DOREPLIFETIME(ARobotCharacter, HitPoints);
  DOREPLIFETIME(ARobotCharacter, Power);
  DOREPLIFETIME(ARobotCharacter, bTargetAcquired);

}

void ARobotCharacter::OnRep_HitPoints()
{
  UE_LOG(LogTemp,Warning,TEXT("%s::OnRep_HitPoints"), *GetName());
  HitPointsChangedDelegate.Broadcast();
}

void ARobotCharacter::OnRep_Power()
{
  UE_LOG(LogTemp,Warning,TEXT("%s::OnRep_Power"), *GetName());
  PowerChangedDelegate.Broadcast();
}

void ARobotCharacter::OnTargetableAdded(AActor* Actor)
{
  UE_LOG(LogTemp,Warning,TEXT("%s::OnTargetableAdded"), *GetName());
  if (HasAuthority() && RobotTargetingComponent->IsTargetable(Actor))
  {
    RobotTargetingComponent->AddTargetable(Actor);
  }
}

void ARobotCharacter::OnTargetableRemoved(AActor* Actor)
{
  UE_LOG(LogTemp,Warning,TEXT("%s::OnTargetableRemoved"), *GetName());
  if (HasAuthority())
  {
    RobotTargetingComponent->RemoveTargetable(Actor);
  }
}

// Targetable Interface
//bool ARobotCharacter::IsTargetableBy(AActor* OtherActor)
//{
//  if (ARobotCharacter* OtherRobotCharacter = Cast<ARobotCharacter>(OtherActor))
//  {
//    return Team != OtherRobotCharacter->Team;
//  }
//
//  return false;
//}
