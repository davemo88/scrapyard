// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotCharacter.h"
#include "Scrapyard.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/RobotGameMode.h"
#include "Robots/RobotMovementComponent.h"
#include "Game/RobotGameState.h"
#include "Player/RobotPlayerController.h"
#include "Player/RobotPlayerState.h"
#include "Game/ScrapyardAssets.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/HUD.h"
#include "Abilities/HitscanAbility.h"
#include "UI/RobotHUDWidget.h"
#include "Parts/HandheldPart.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "DrawDebugHelpers.h"
#include "UnrealNetwork.h"
#include "Math/UnrealMathVectorConstants.h"
#include "Engine.h"

// Sets default values
ARobotCharacter::ARobotCharacter(const class FObjectInitializer& ObjectInitializer)
//  : Super(ObjectInitializer)
  : Super(ObjectInitializer.SetDefaultSubobjectClass<URobotMovementComponent>(ARobotCharacter::CharacterMovementComponentName))
{
  UE_LOG(LogCharacter, Log, TEXT("%s::ARobotCharacter"), *GetName());
   // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

//  ControlType = EControlType::CONTROL_Normal;
//  ControlType = EControlType::CONTROL_Rectangle;
  ControlType = EControlType::CONTROL_Ellipse;

  bReplicates = true;
  bAlwaysRelevant = true;

  PartAssignment = CreateDefaultSubobject<UPartAssignment>(TEXT("PartAssignment"));
  PartAssignment->SetDefaultAssignment();

  SetupCamera();
  SetupBody();
  SetupStats();

  if (URobotMovementComponent* RobotMovementComponent = Cast<URobotMovementComponent>(GetCharacterMovement()))
  {
    RobotMovementComponent->SetNetAddressable();
    RobotMovementComponent->SetIsReplicated(true); 
  }

  RobotTargetingComponent = CreateDefaultSubobject<URobotTargetingComponent>(TEXT("RobotTargetingComponent")); 
  RobotTargetingComponent->SetupAttachment(RootComponent);

//TODO: refactor to get rid of ARobotCharacter tick event
// NOTE: maybe sloppy but also seems to make sense
  AddTickPrerequisiteComponent(RobotTargetingComponent);

  TargetableComponent = CreateDefaultSubobject<UTargetableComponent>(TEXT("TargetableComponent"));

}

// Called when the game starts or when spawned
void ARobotCharacter::BeginPlay()
{
  Super::BeginPlay();
  const UEnum* NetRoleEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ENetRole"));
  UE_LOG(LogCharacter, Log, TEXT("%s::BeginPlay - Role: %s"), *GetName(), *(NetRoleEnum ? NetRoleEnum->GetNameStringByIndex(Role) : TEXT("oops")));
  UE_LOG(LogCharacter, Log, TEXT("%s::BeginPlay - RemoteRole: %s"), *GetName(), *(NetRoleEnum ? NetRoleEnum->GetNameStringByIndex(GetRemoteRole()) : TEXT("oops")));

//TODO: this shouldn't be here
  if (ARobotPlayerController* PC = Cast<ARobotPlayerController>(GetController()))
  {
    UE_LOG(LogCharacter, Log, TEXT("%s::BeginPlay - PC ok"), *GetName());
    PC->SetRobotCharacter(this);
//    if (IsLocallyControlled())
//    {
//      UE_LOG(LogCharacter, Log, TEXT("%s::BeginPlay - Local PC"), *GetName());
//      SetupRobotHUDWidget();
//    }
  }
}

void ARobotCharacter::PostInitializeComponents()
{
  UE_LOG(LogCharacter, Log, TEXT("%s::PostInitializeComponents"), *GetName());
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
//TODO: we can remove this tick event
  Super::Tick(DeltaTime);
//  UE_LOG(LogCharacter, Log, TEXT("%s::Tick"), *GetName());
  const FVector RobotLoc = GetActorLocation() + RobotBodyComponent->GetComponentRotation().RotateVector(FVector(-70,220,70));
//  DrawDebugSphere(GetWorld(), RobotLoc, 20, 10, FColor::Red);

}

// Called to bind functionality to input
void ARobotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  UE_LOG(LogCharacter, Log, TEXT("%s::SetupPlayerInputComponent"), *GetName());

  Super::SetupPlayerInputComponent(PlayerInputComponent);

  ARobotPlayerController* PC = Cast<ARobotPlayerController>(GetController());

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

void ARobotCharacter::Landed(const FHitResult & Hit)
{
  Super::Landed(Hit);

  URobotMovementComponent* MoveComp = Cast<URobotMovementComponent>(GetCharacterMovement());

  MoveComp->Landed(Hit);

}

void ARobotCharacter::Restart()
{
  Super::Restart();
  UE_LOG(LogCharacter, Log, TEXT("%s::Restart"), *GetName());
  if (IsLocallyControlled())
  {
    SetupRobotHUDWidget();
  }
}

void ARobotCharacter::SetupRobotHUDWidget()
{
  UE_LOG(LogCharacter, Log, TEXT("%s::SetupRobotHUDWidget"), *GetName());
  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
  ARobotPlayerController* PC = Cast<ARobotPlayerController>(GetController());
  if (PC && IsLocallyControlled())
  {
// TODO: perhaps refactor creation of the widget so the widget itself doesn't have to be public
// e.g. use friend class or write a function
    UE_LOG(LogCharacter, Log, TEXT("%s::SetupRobotHUDWidget - local PC"), *GetName());
    PC->RobotHUDWidget = CreateWidget<URobotHUDWidget>(PC, GameInstance->AssetsBP->UIAssetsBP->RobotHUDWidgetBP);
    PC->RobotHUDWidget->SetRobotCharacter(this);
    PC->RobotHUDWidget->AddToViewport();

//    PC->EscapeMenuWidget->TunerWidget->SetRobotChar(this);

  }
  else
  {
    UE_LOG(LogCharacter, Log, TEXT("%s::SetupRobotHUDWidget - nonlocal or null PC"), *GetName());
  }
}

void ARobotCharacter::SetupCamera()
{
  RootComponent = GetRootComponent();

  CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
  CameraBoom->SetupAttachment(RootComponent);

  CameraBoom->bAbsoluteRotation = false;
  CameraBoom->TargetArmLength = 500.f;
  CameraBoom->SocketOffset = FVector(0.f, 0.f, 200.f);
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
//  RobotBodyComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -88.f));
// rotation ?
// seems like the sketetal mesh is not set up correctly
  RobotBodyComponent->SetRelativeRotation(FRotator(0.0f,-90.0f,0.f));

  RobotBodyComponent->SetPartAssignment(PartAssignment);

}

void ARobotCharacter::SetupStats()
{
  RobotStats = CreateDefaultSubobject<URobotStats>(TEXT("RobotStats"));
  RobotStats->RobotStatsUpdatedDelegate.AddDynamic(this, &ARobotCharacter::OnStatsUpdated);
  RobotStats->SetPartAssignment(PartAssignment);
}

void ARobotCharacter::SetupAbilities()
{
  UE_LOG(LogCharacter, Log, TEXT("%s::SetupAbilities"), *GetName());
//  const UEnum* NetRoleEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ENetRole"));
//  UE_LOG(LogCharacter, Log, TEXT("%s::SetupAbilities - Role: %s"), *GetName(), *(NetRoleEnum ? NetRoleEnum->GetNameStringByIndex(Role) : TEXT("oops")));
//  UE_LOG(LogCharacter, Log, TEXT("%s::SetupAbilities - RemoteRole: %s"), *GetName(), *(NetRoleEnum ? NetRoleEnum->GetNameStringByIndex(GetRemoteRole()) : TEXT("oops")));

  if (PartAssignment->GetRightHandheld() && PartAssignment->GetRightHandheld()->AbilityClass)
  {
    WeaponAbility = GetWorld()->SpawnActor<AScrapyardAbility>(PartAssignment->GetRightHandheld()->AbilityClass, FActorSpawnParameters());

    UE_LOG(LogCharacter, Log, TEXT("Weapon Name: %s"), *PartAssignment->GetRightHandheld()->PartName.ToString());
    UE_LOG(LogCharacter, Log, TEXT("Weapon Ability Class Name: %s"), *PartAssignment->GetRightHandheld()->AbilityClass->GetName());

// TODO: why do we have RobotOwner if we can just the real Owner?
// TODO: why setting owner in two different ways here? seems just wrong
// BUG: should only set owner on the server
    WeaponAbility->RobotOwner = this;
    WeaponAbility->SetOwner(this);
    UE_LOG(LogCharacter, Log, TEXT("Weapon Ability Replication: %s"), (WeaponAbility->GetIsReplicated() ? TEXT("True") : TEXT("False")));
  }

}

void ARobotCharacter::OnStatsUpdated()
{
  UE_LOG(LogCharacter, Log, TEXT("%s::OnStatsUpdated"), *GetName());
  UE_LOG(LogCharacter, Log, TEXT("HitPoints: %i"), RobotStats->HitPoints);
  UE_LOG(LogCharacter, Log, TEXT("Power: %i"), RobotStats->MaxPower);

//TODO: functions to do these
//TODO: Q: why aren't these updated on replication?
//A: because the event isn't broadcast on the client via an RPC
  HitPoints = RobotStats->HitPoints;
  HitPointsChangedDelegate.Broadcast();
  Power = RobotStats->MaxPower;
  PowerChangedDelegate.Broadcast();
}

void ARobotCharacter::Axis_MoveX(float AxisValue)
{
  if (Controller && AxisValue != 0.f)
  {
    // Limit pitch when walking or falling
    URobotMovementComponent* MovementComponent = Cast<URobotMovementComponent>(GetMovementComponent());
    const bool bLimitRotation = (MovementComponent->IsMovingOnGround() || MovementComponent->IsFalling() || MovementComponent->IsFlying());

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
//  UE_LOG(LogCharacter, Log, TEXT("ARobotCharacter::Axis_TurnZ - value: %f time: %f"), AxisValue, realtimeSeconds);

  float TurnRate = 0;

  if (ControlType == EControlType::CONTROL_Ellipse)
  {
    FIntPoint MousePoint;
    GetWorld()->GetGameViewport()->Viewport->GetMousePos(MousePoint);
    FVector2D Mouse = FVector2D(MousePoint);
  
    if (Mouse.X != -1 && !IsInControlEllipse(Mouse))
    {
      const FVector2D ViewSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
      const float CenterX = ViewSize.X / 2;
      const FVector2D Intersection = GetControlEllipseIntersection(FVector2D(Mouse.X, Mouse.Y));
// Y = 0 is the top of the viewport
      float ControlMax = Mouse.X < CenterX
        ? Intersection.X
        : ViewSize.X - Intersection.X;

      TurnRate = (Mouse.X - Intersection.X) / ControlMax;
    }
//    UE_LOG(LogCharacter, Log, TEXT("TurnZ Rate: %f"), TurnRate);
  }
  else if (ControlType == EControlType::CONTROL_Rectangle)
  {
    FIntPoint MousePoint;
    GetWorld()->GetGameViewport()->Viewport->GetMousePos(MousePoint);
    FVector2D Mouse = FVector2D(MousePoint);

//    UE_LOG(LogCharacter, Log, TEXT("mouse position: %fx %fy"), MouseX, MouseY);

    const FVector2D ViewSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
    const FVector2D Center = ViewSize / 2;
    const FVector2D DeadZoneHalfWidth = GetDeadZoneHalfWidth();

    if (Mouse.X != -1 && !IsInXDeadZone(Mouse))
    {
//      UE_LOG(LogCharacter, Log, TEXT("mouse position: %fx %fy"), Mouse.X, Mouse.Y);
      float ControlMax = Center.X - DeadZoneHalfWidth.X;
      TurnRate = Mouse.X < Center.X
        ? (Mouse.X - Center.X + DeadZoneHalfWidth.X) / ControlMax
        : (Mouse.X - Center.X - DeadZoneHalfWidth.X) / ControlMax;
    }
//    UE_LOG(LogCharacter, Log, TEXT("TurnZ Rate: %f"), TurnRate);
  }
  else
  {
//  UE_LOG(LogCharacter, Log, TEXT("ARobotCharacter::Axis_TurnZ - AxisValue : %f"), AxisValue);
    TurnRate = FMath::Clamp(AxisValue, -1.0f, 1.0f);
  }

  AddControllerYawInput(TurnRate * RobotStats->TurningSpeed);
}

void ARobotCharacter::Axis_TurnY(float AxisValue)
{

// TODO: serverside validation of turn rates
  float TurnRate = 0;

  if (ControlType == EControlType::CONTROL_Ellipse)
  {
    FIntPoint MousePoint;
    GetWorld()->GetGameViewport()->Viewport->GetMousePos(MousePoint);
    FVector2D Mouse = FVector2D(MousePoint);

    if (Mouse.X != -1 && !IsInControlEllipse(Mouse))
    {
      const FVector2D ViewSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
      const float CenterY = ViewSize.Y / 2;
      const FVector2D Intersection = GetControlEllipseIntersection(FVector2D(Mouse.X, Mouse.Y));
// Y = 0 is the top of the viewport
      float ControlMax = Mouse.Y < CenterY
        ? Intersection.Y
        : ViewSize.Y - Intersection.Y;

      TurnRate = (Mouse.Y - Intersection.Y) / ControlMax;
    }

//    UE_LOG(LogCharacter, Log, TEXT("TurnY Rate: %f"), TurnRate);
  }
  else if (ControlType == EControlType::CONTROL_Rectangle)
  {
    FIntPoint MousePoint;
    GetWorld()->GetGameViewport()->Viewport->GetMousePos(MousePoint);
    FVector2D Mouse = FVector2D(MousePoint);

//    UE_LOG(LogCharacter, Log, TEXT("mouse position: %fx %fy"), MouseX, MouseY);

    const FVector2D ViewSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
    const FVector2D Center = ViewSize / 2;
    const FVector2D DeadZoneHalfWidth = GetDeadZoneHalfWidth();

    if (Mouse.X != -1 && !IsInYDeadZone(Mouse))
    {
//      UE_LOG(LogCharacter, Log, TEXT("mouse position: %fx %fy"), Mouse.Y, Mouse.Y);
      float ControlMax = Center.Y - DeadZoneHalfWidth.Y;
      TurnRate = Mouse.Y < Center.Y
        ? (Mouse.Y - Center.Y + DeadZoneHalfWidth.Y) / ControlMax
        : (Mouse.Y - Center.Y - DeadZoneHalfWidth.Y) / ControlMax;
    }

//    UE_LOG(LogCharacter, Log, TEXT("TurnY Rate: %f"), TurnRate);
  }
  else
  {
    TurnRate = FMath::Clamp(AxisValue, -1.0f, 1.0f);
  }

  AddControllerPitchInput(TurnRate * MaxPitchRate);
}

void ARobotCharacter::StartBoosting()
{
  UE_LOG(LogCharacter, Log, TEXT("%s::StartBoosting"), *GetName());
  URobotMovementComponent* MoveComp = Cast<URobotMovementComponent>(GetCharacterMovement());
  if (MoveComp)
  {
    MoveComp->SetBoostInput(1);
  }
}

void ARobotCharacter::StopBoosting()
{
  UE_LOG(LogCharacter, Log, TEXT("%s::StopBoosting"), *GetName());
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
  UE_LOG(LogCharacter, Log, TEXT("ARobotCharacter::TakeDamage"));

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
    UE_LOG(LogCharacter, Log, TEXT("%s::TakeDamage - HitPoints set to %d"), *GetName(), HitPoints);
    HitPointsChangedDelegate.Broadcast();

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
  UE_LOG(LogCharacter,Log,TEXT("%s::StartFire"), *GetName());

  if (!IsLocallyControlled())
  {
    UE_LOG(LogCharacter, Log, TEXT("StartFire can only be called on the owning client"));
  }
  else
  {
    if (WeaponAbility != NULL)
    {
      WeaponAbility->StartFire(FireModeNum);
    }
    else
    {
      UE_LOG(LogCharacter, Log, TEXT("ARobotCharacter::WeaponAbility is NULL"));
    }
  }
}

void ARobotCharacter::StopFire(uint8 FireModeNum)
{
  UE_LOG(LogCharacter,Log,TEXT("ARobotCharacter::StopFire"));
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

}

void ARobotCharacter::OnRep_HitPoints()
{
  UE_LOG(LogCharacter,Log,TEXT("%s::OnRep_HitPoints"), *GetName());
  HitPointsChangedDelegate.Broadcast();
}

void ARobotCharacter::OnRep_Power()
{
  UE_LOG(LogCharacter,Log,TEXT("%s::OnRep_Power"), *GetName());
  PowerChangedDelegate.Broadcast();
}

bool ARobotCharacter::IsTargetAcquired()
{
  return RobotTargetingComponent->IsTargetAcquired();
}

bool ARobotCharacter::IsTargetableBy(ARobotCharacter* Robot)
{
  return Team != Robot->Team;
}

void ARobotCharacter::SetPartAssignment(UPartAssignment* NewPartAssignment)
{
  UE_LOG(LogCharacter, Log, TEXT("%s::SetPartAssignment"), *GetName());
  PartAssignment = NewPartAssignment;
  RobotStats->SetPartAssignment(PartAssignment);
  RobotBodyComponent->SetPartAssignment(PartAssignment);
  if (HasAuthority())
  {
    SetupAbilities();
  }
}

void ARobotCharacter::MulticastSetPartAssignmentFromIDs_Implementation(FPartAssignmentIDs NewPartAssignmentIDs)
{
  UE_LOG(LogCharacter, Log, TEXT("%s::MulticastSetPartAssignmentFromIDs_Implementation"), *GetName());
  UE_LOG(LogCharacter, Log, TEXT("Head PartID: %d"), NewPartAssignmentIDs.HeadID);
  UE_LOG(LogCharacter, Log, TEXT("Core PartID: %d"), NewPartAssignmentIDs.CoreID);
  UE_LOG(LogCharacter, Log, TEXT("Arms PartID: %d"), NewPartAssignmentIDs.ArmsID);
  UE_LOG(LogCharacter, Log, TEXT("Legs PartID: %d"), NewPartAssignmentIDs.LegsID);
  UPartAssignment* NewAssignment = NewObject<UPartAssignment>();
  NewAssignment->SetAssignment(NewPartAssignmentIDs);
  SetPartAssignment(NewAssignment);
//  PartAssignment->SetAssignment(NewPartAssignmentIDs);
}

FVector2D ARobotCharacter::GetControlEllipseIntersection(FVector2D Mouse)
{
  const FVector2D ViewSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());

  float CenterX = ViewSize.X / 2;
  float CenterY = ViewSize.Y / 2;

  FVector2D CenteredMousePos = FVector2D(Mouse.X - CenterX, Mouse.Y - CenterY);

// slope of line from origin to cursor position
  float m = CenteredMousePos.Y / CenteredMousePos.X;

// control ellipse horizontal axis
  float a = GetDeadZoneHalfWidth().X;
// control ellipse vertical axis
  float b = GetDeadZoneHalfWidth().Y;

// intersection between line from origin to mouse and ellipse
  FVector2D CenteredIntersection;

  CenteredIntersection.X = a * b * FMath::Sqrt(1/(FMath::Square(b) + FMath::Square(a * m)));
  CenteredIntersection.X = CenteredMousePos.X > 0 ? CenteredIntersection.X : -CenteredIntersection.X;
  CenteredIntersection.Y = m * CenteredIntersection.X;

  return FVector2D(CenteredIntersection.X + CenterX, CenteredIntersection.Y + CenterY);
}

bool ARobotCharacter::IsInControlEllipse(FVector2D Mouse)
{
  const FVector2D ViewSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
  const FVector2D Center = ViewSize / 2;
  const FVector2D Axes = GetDeadZoneHalfWidth();
  
  return FMath::Square(Mouse.X - Center.X) / FMath::Square(Axes.X) + (FMath::Square(Mouse.Y - Center.Y)) / FMath::Square(Axes.Y) <= 1;
}

bool ARobotCharacter::IsInXDeadZone(FVector2D Mouse)
{
  const FVector2D ViewSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
  const FVector2D Center = ViewSize / 2;
  const FVector2D DeadZoneHalfWidth = GetDeadZoneHalfWidth();
  const FVector2D DeadZoneMin = Center - DeadZoneHalfWidth;
  const FVector2D DeadZoneMax = Center + DeadZoneHalfWidth;

  return Mouse.X > DeadZoneMin.X  && Mouse.X < DeadZoneMax.X;
}

bool ARobotCharacter::IsInYDeadZone(FVector2D Mouse)
{
  const FVector2D ViewSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
  const FVector2D Center = ViewSize / 2;
  const FVector2D DeadZoneHalfWidth = GetDeadZoneHalfWidth();
  const FVector2D DeadZoneMin = Center - DeadZoneHalfWidth;
  const FVector2D DeadZoneMax = Center + DeadZoneHalfWidth;

  return Mouse.Y > DeadZoneMin.Y  && Mouse.Y < DeadZoneMax.Y;
}

FVector2D ARobotCharacter::GetDeadZoneHalfWidth()
{
  return UWidgetLayoutLibrary::GetViewportSize(GetWorld()) / DeadZoneFactor;
}
