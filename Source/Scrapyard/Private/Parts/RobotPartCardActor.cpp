// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPartCardActor.h"



// Sets default values
ARobotPartCardActor::ARobotPartCardActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ClickableComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ClickableComponent"));
	ClickableComponent->SetCollisionResponseToAllChannels(ECR_Block);
	ClickableComponent->bHiddenInGame = false;
	RootComponent = ClickableComponent;

	RobotPart = CreateDefaultSubobject<URobotPart>(TEXT("RobotPart"));
	CardTitleComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CardTitleComponent"));
	CardTitleComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ARobotPartCardActor::BeginPlay()
{
	Super::BeginPlay();

	OnClicked.AddUniqueDynamic(this, &ARobotPartCardActor::DoOnClicked);
	
}

void ARobotPartCardActor::DoOnClicked(AActor* Target, FKey ButtonPressed)
{
	UE_LOG(LogTemp, Warning, TEXT("clicked %s"), *RobotPart->PartName);
	OnRobotPartCardClicked.Broadcast(RobotPart);
}

// Called every frame
void ARobotPartCardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARobotPartCardActor::SetRobotPart(URobotPart* NewRobotPart)
{
	RobotPart = NewRobotPart;
	CardTitleComponent->SetText(FText::FromString(RobotPart->PartName));
}

