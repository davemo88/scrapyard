// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotGameMode.h"
#include "Engine/Engine.h"
#include "UObjectGlobals.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Robots/RobotCharacter.h"
#include "Player/ScrapyardPlayerController.h"

ARobotGameMode::ARobotGameMode()
{
	DefaultPawnClass = ARobotCharacter::StaticClass();
	PlayerControllerClass = AScrapyardPlayerController::StaticClass();
}

void ARobotGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(LogTemp, Warning, TEXT("Num Players: %i"), NumPlayers);
	UE_LOG(LogTemp, Warning, TEXT("Num PlayerController: %i"), NumPlayers);
	for (TActorIterator<APlayerController> ActrItr(GetWorld()); ActrItr; ++ActrItr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("here's a controller")));
	}
}
