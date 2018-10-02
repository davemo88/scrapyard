// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraActor.h"
#include "SoloDraftActor.generated.h"

class USoloDraft;
class UHeadPart;
class UCorePart;
class UArmsPart;
class ULegsPart;
class ARobotPartActor;


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

//	TArray<UHeadPart*> HeadParts;
//	TArray<UCorePart*> CoreParts;
//	TArray<UArmsPart*> ArmsParts;
//	TArray<ULegsPart*> LegsParts;
        
	TArray<TSubclassOf<UHeadPart>> HeadParts;
	TArray<TSubclassOf<UCorePart>> CoreParts;
	TArray<TSubclassOf<UArmsPart>> ArmsParts;
	TArray<TSubclassOf<ULegsPart>> LegsParts;

	void SpawnDraftCamera();

	ARobotPartActor* SpawnRobotPartActor(
//		URobotPart* RobotPart,
		TSubclassOf<URobotPart> RobotPartClass,
		FVector Loc = FVector(0.0f, 0.0f, 0.0f),
		FRotator Rot = FRotator(0.0f, 0.0f, 0.0f),
		FActorSpawnParameters SpawnParams = FActorSpawnParameters()
	);

	void SpawnPartCards();
	void DestroyPartCards();

	void NextPack();

	void SamplePack();

        UPROPERTY()
        TArray<ARobotPartActor*> PartActors;

	template<typename T>
//	T* SamplePart(TArray<T*>& Parts, bool Replacement = true);
	T SamplePart(TArray<T>& Parts, bool Replacement = true);

	UFUNCTION()
	void DraftPart(URobotPart* RobotPart);
//	void DraftPart(TSubclassOf<URobotPart> RobotPart);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//TODO needs to be uproperty or attributes get GC'ed ??
	UPROPERTY(VisibleAnywhere)
	USoloDraft* CurrentDraft;

};
