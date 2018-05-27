// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotCharacter.h"
#include "Game/ScrapyardGameInstance.h"
#include "Robots/RobotMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ARobotCharacter::ARobotCharacter(const class FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<URobotMovementComponent>(ARobotCharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bAlwaysRelevant = true;

	SetupCamera();
	SetupPartAssignment();
	SetupBody();
	SetupStats();

// allow flying movement
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
    PlayerInputComponent->BindAxis("MoveX", this, &ARobotCharacter::Axis_MoveX);
    PlayerInputComponent->BindAxis("MoveY", this, &ARobotCharacter::Axis_MoveY);

    PlayerInputComponent->BindAxis("TurnZ", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("TurnY", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARobotCharacter::Jump);

	PlayerInputComponent->BindAxis("Boost", this, &ARobotCharacter::Axis_Boost);
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

void ARobotCharacter::SetupPartAssignment()
{
	RobotPartAssignment = CreateDefaultSubobject<URobotPartAssignment>(TEXT("RobotPartAssignment"));
	UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstance)
	{
		if (!GameInstance->RobotPartAssignment->IsComplete())
		{
			UE_LOG(LogTemp, Warning, TEXT("setting default part assignment"));
			RobotPartAssignment->SetDefaultAssignment();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("setting game instance part assignment"));
			RobotPartAssignment = GameInstance->RobotPartAssignment;
		}
	}
}

void ARobotCharacter::SetupBody()
{
	RobotBodyComponent = CreateDefaultSubobject<URobotBodyComponent>(TEXT("RobotBodyComponent"));
	if (RobotPartAssignment->IsComplete())
	{
		RobotBodyComponent->SetPartAssignment(RobotPartAssignment);
	}

	RootComponent = GetRootComponent();
	RobotBodyComponent->SetupAttachment(RootComponent);

// need that magic DO_REPLIFETIME(?) function
//	RobotBodyComponent->SetIsReplicated(true);
}

void ARobotCharacter::SetupStats()
{
	RobotStats = CreateDefaultSubobject<URobotStats>(TEXT("RobotStats"));
}

void ARobotCharacter::UpdateStats()
{
//	RobotStats->MaxDurability += RobotPartAssignment->Head->Durability;
//	RobotStats->MaxDurability += RobotPartAssignment->Core->Durability;
//	RobotStats->MaxDurability += RobotPartAssignment->Arms->Durability;
//	RobotStats->MaxDurability += RobotPartAssignment->Legs->Durability;

////	RobotStats->MaxPower += RobotPartAssignment->PowerPlant->PowerSupply;
	RobotStats->MaxPower += 1000;

}

void ARobotCharacter::Axis_MoveX(float AxisValue)
{
	if (Controller && AxisValue != 0.f)
	{
		// Limit pitch when walking or falling
		URobotMovementComponent* MovementComponent = Cast<URobotMovementComponent>(GetMovementComponent());
		const bool bLimitRotation = (MovementComponent->IsMovingOnGround() || MovementComponent->IsFalling() || MovementComponent->IsFlying());
//		const bool bLimitRotation = (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling());
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
//	UE_LOG(LogTemp, Warning, TEXT("Preboost Movement Mode: %s "), *MovementModeName);
	if (AxisValue != 0.f && Power > 0)
	{
		Power = Power - (int)(10 * AxisValue);
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
		if (Power < 1000)
//		if (Power < RobotStats->MaxPower)
		{
			Power = Power + 10;
		}

		if (MovementComponent->IsFlying())
		{
			MovementComponent->SetMovementMode(MOVE_Falling, 3);
		}
	};
//	UE_LOG(LogTemp, Warning, TEXT("Postboost Movement Mode: %s "), *MovementModeName);

// better to switch on this enum type later
//	EMovementMode MovementMode = MovementComponent->MovementMode;
}
