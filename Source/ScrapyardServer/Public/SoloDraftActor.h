// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraActor.h"
#include "SoloDraft.h"
#include "HeadPart.h"
#include "CorePart.h"
#include "ArmsPart.h"
#include "LegsPart.h"
#include "RobotPartCardActor.h"
#include "SoloDraftActor.generated.h"


UCLASS()
class SCRAPYARDSERVER_API ASoloDraftActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoloDraftActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	TArray<UHeadPart*> HeadParts;
	TArray<UCorePart*> CoreParts;
	TArray<UArmsPart*> ArmsParts;
	TArray<ULegsPart*> LegsParts;

	void SpawnDraftCamera();

	ARobotPartCardActor* SpawnRobotPartCardActor(
		URobotPart* RobotPart,
		FVector Loc = FVector(0.0f, 0.0f, 0.0f),
		FRotator Rot = FRotator(0.0f, 0.0f, 0.0f),
		FActorSpawnParameters SpawnParams = FActorSpawnParameters()
	);

	void SpawnPartCards();
	void DestroyPartCards();

	void NextPack();

	void SamplePack();

        UPROPERTY()
        TArray<ARobotPartCardActor*> PartCardActors;

	template<typename T>
	T* SamplePart(TArray<T*>& Parts, bool Replacement = true);

	UFUNCTION()
	void DraftPart(URobotPart* RobotPart);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//TODO needs to be uproperty or attributes get GC'ed ??
	UPROPERTY(VisibleAnywhere)
	USoloDraft* CurrentDraft;

};
