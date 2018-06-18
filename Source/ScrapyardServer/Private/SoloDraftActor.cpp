// Fill out your copyright notice in the Description page of Project Settings.

#include "SoloDraftActor.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "UObjectGlobals.h"
#include "ScrapyardGameInstance.h"


// Sets default values
ASoloDraftActor::ASoloDraftActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CurrentDraft = CreateDefaultSubobject<USoloDraft>(TEXT("CurrentDraft"));

	RobotPartHelper = CreateDefaultSubobject<URobotPartHelper>(TEXT("RobotPartHelper"));

}

// Called when the game starts or when spawned
void ASoloDraftActor::BeginPlay()
{
	Super::BeginPlay();

	HeadParts = RobotPartHelper->GetAllHeads();
	CoreParts = RobotPartHelper->GetAllCores();
	ArmsParts = RobotPartHelper->GetAllArms();
	LegsParts = RobotPartHelper->GetAllLegs();

	SpawnDraftCamera();

	NextPack();


}

// Called every frame
void ASoloDraftActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASoloDraftActor::SpawnDraftCamera()
{
	UWorld* World = GetWorld();
	ACameraActor* DraftCamera = World->SpawnActor<ACameraActor>(FVector(-420.0f, 0.0f, 200.0f), FRotator(0.0f, 0.0f, 0.0f), FActorSpawnParameters());
	World->GetFirstPlayerController()->SetViewTarget(DraftCamera);
}

ARobotPartCardActor* ASoloDraftActor::SpawnRobotPartCardActor(URobotPart* RobotPart, FVector Loc, FRotator Rot, FActorSpawnParameters SpawnParams)
{
	UWorld* World = GetWorld();
	ARobotPartCardActor* CardActor = World->SpawnActor<ARobotPartCardActor>(Loc, Rot, SpawnParams);
	CardActor->SetRobotPart(RobotPart);
	CardActor->OnRobotPartCardClicked.AddDynamic(this, &ASoloDraftActor::DraftPart);
	return CardActor;
}

void ASoloDraftActor::SpawnPartCards()
{
	if (CurrentDraft->CurrentPack->IsComplete())
	{
		ARobotPartCardActor* HeadPartCardActor = SpawnRobotPartCardActor(CurrentDraft->CurrentPack->Head, FVector(0,-100,200), FRotator(0.0f, 180.f, 0.f));
		ARobotPartCardActor* CorePartCardActor = SpawnRobotPartCardActor(CurrentDraft->CurrentPack->Core, FVector(0,100,200), FRotator(0.0f, 180.f, 0.f));
		ARobotPartCardActor* ArmsPartCardActor = SpawnRobotPartCardActor(CurrentDraft->CurrentPack->Arms, FVector(0,-100,300), FRotator(0.0f, 180.f, 0.f));
		ARobotPartCardActor* LegsPartCardActor = SpawnRobotPartCardActor(CurrentDraft->CurrentPack->Legs, FVector(0,100,300), FRotator(0.0f, 180.f, 0.f));
	}
}

void ASoloDraftActor::DestroyPartCards()
{
	for (TActorIterator<ARobotPartCardActor> ActrItr(GetWorld()); ActrItr; ++ActrItr)
	{
		ActrItr->Destroy();
	}
}

void ASoloDraftActor::NextPack()
{
	DestroyPartCards();
	CurrentDraft->CurrentPack = SamplePack();
	SpawnPartCards();
}

URobotPartAssignment* ASoloDraftActor::SamplePack()
{
	URobotPartAssignment* Pack = NewObject<URobotPartAssignment>();

//	if (Role == ROLE_Authority)
//	{
		Pack->Head = SamplePart<UHeadPart>(HeadParts);
		Pack->Core = SamplePart<UCorePart>(CoreParts);
	 	Pack->Arms = SamplePart<UArmsPart>(ArmsParts);
		Pack->Legs = SamplePart<ULegsPart>(LegsParts);
//	}

	return Pack;
}

template<typename T>
T* ASoloDraftActor::SamplePart(TArray<T*>& Parts, bool Replacement)
{
	int32 NumParts = Parts.Num();
	T* RobotPart = nullptr;
	if (NumParts > 0)
	{
		int Index = FMath::RandRange(0, NumParts - 1);
		RobotPart = Parts[Index];
		if (!Replacement)
		{
			Parts.RemoveAt(Index);
		}
	}
	return RobotPart;
}

void ASoloDraftActor::DraftPart(URobotPart* RobotPart)
{
	UE_LOG(LogTemp, Warning, TEXT("drafting %s"), *RobotPart->PartName);
	CurrentDraft->Picks++;
	RobotPart->Draft(CurrentDraft);

	UE_LOG(LogTemp, Warning, TEXT("num heads %i"), CurrentDraft->DraftedHeads.Num());
	UE_LOG(LogTemp, Warning, TEXT("num cores %i"), CurrentDraft->DraftedCores.Num());
	UE_LOG(LogTemp, Warning, TEXT("num arms %i"), CurrentDraft->DraftedArms.Num());
	UE_LOG(LogTemp, Warning, TEXT("num legs %i"), CurrentDraft->DraftedLegs.Num());

	if (CurrentDraft->Picks < CurrentDraft->MaxPicks)
	{
		NextPack();
	}
	else
	{
		UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
		if (CurrentDraft != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("draft complete"));
			GameInstance->SoloDraft = DuplicateObject(CurrentDraft, NULL);
			UGameplayStatics::OpenLevel(GetWorld(), "/Game/Levels/GarageLevel");
		}
	}
}
