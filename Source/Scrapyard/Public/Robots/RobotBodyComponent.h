// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Robots/RobotPartComponent.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Robots/RobotPartAssignment.h"
#include "UObject/ConstructorHelpers.h"
#include "RobotBodyComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCRAPYARD_API URobotBodyComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URobotBodyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// default skeletal mesh
	FString DefaultMeshPath = "/Game/Mannequin/Mesh/SK_Mannequin";

// animation instance class
// https://answers.unrealengine.com/questions/153496/how-to-set-animation-blueprint-in-c.html
	FString DefaultAnimPath = "AnimBlueprintGeneratedClass'/Game/Mannequin/Animations/MannequinAnimBlueprint.MannequinAnimBlueprint_C'";

// part assignment
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URobotPartAssignment* RobotPartAssignment;

// part components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URobotPartComponent* HeadComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URobotPartComponent* CoreComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URobotPartComponent* ArmsComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URobotPartComponent* LegsComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URobotPartComponent* RightHandheldComponent;

//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	UParticleSystemComponent* BoostingParticleComponent;

	UFUNCTION(BlueprintCallable)
	void SetPartAssignment(URobotPartAssignment* PartAssignment);

// if these weren't UFUNCTIONs then I could write an overloaded function
	UFUNCTION(BlueprintCallable)
	void SetHead(UHeadPart* NewHead);
	UFUNCTION(BlueprintCallable)
	void SetCore(UCorePart* NewCore);
	UFUNCTION(BlueprintCallable)
	void SetArms(UArmsPart* NewArms);
	UFUNCTION(BlueprintCallable)
	void SetLegs(ULegsPart* NewLegs);
};