// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPartActor.h"

// Sets default values
ARobotPartActor::ARobotPartActor()
{
   // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  ClickableComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ClickableComponent"));
  ClickableComponent->SetCollisionResponseToAllChannels(ECR_Block);
  ClickableComponent->bHiddenInGame = false;
  RootComponent = ClickableComponent;

//  RobotPart = CreateDefaultSubobject<URobotPart>(TEXT("RobotPart"));
  TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CardTitleComponent"));
  TextComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ARobotPartActor::BeginPlay()
{
  UE_LOG(LogTemp, Warning, TEXT("ARobotPartActor::BeginPlay")); 
  Super::BeginPlay();

  OnClicked.AddUniqueDynamic(this, &ARobotPartActor::DoOnClicked);
  
}

void ARobotPartActor::DoOnClicked(AActor* Target, FKey ButtonPressed)
{
  UE_LOG(LogTemp, Warning, TEXT("clicked %s"), *RobotPart->PartName);
  OnRobotPartClicked.Broadcast(RobotPart);
}

//void ARobotPartActor::SetRobotPart(URobotPart* NewRobotPart)
void ARobotPartActor::SetRobotPart(URobotPart* NewRobotPart)
{
  UE_LOG(LogTemp, Warning, TEXT("ARobotPartActor::SetRobotPart"));
  RobotPart = NewRobotPart;
//  RobotPart->SetupAttachment(GetRootComponent());
//  RobotPart->RegisterComponent();
//  RobotPart->SetVisibility(false);
  TextComponent->SetText(FText::FromString(RobotPart->PartName));
}

