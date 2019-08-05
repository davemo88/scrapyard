// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PartAssignment.generated.h"

class UHeadPart;
class UCorePart;
class UArmsPart;
class ULegsPart;
class UBoosterPart;
class UHandheldPart;
class UChipPart;

USTRUCT()
struct FPartAssignmentIDs
{
  GENERATED_BODY()

  UPROPERTY()
  uint32 HeadID;
  UPROPERTY()
  uint32 CoreID;
  UPROPERTY()
  uint32 ArmsID;
  UPROPERTY()
  uint32 LegsID;
  UPROPERTY()
  uint32 BoosterID;
  UPROPERTY()
  uint32 LeftHandheldID;
  UPROPERTY()
  uint32 RightHandheldID;
//NOTE: hard to say how to implement dynamic number of chips but it can't be much more than 3 max
  UPROPERTY()
  uint32 FirstChipID;
  UPROPERTY()
  uint32 SecondChipID;
  UPROPERTY()
  uint32 ThirdChipID;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNoParamAssignmentChangedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAssignmentChangedDelegate, URobotPart*, NewPart);

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UPartAssignment : public UObject
{
  GENERATED_BODY()

public:

  bool IsComplete() const;

  void SetHead(UHeadPart* NewHead);
  void SetCore(UCorePart* NewCore);
  void SetArms(UArmsPart* NewArms);
  void SetLegs(ULegsPart* NewLegs);
  void SetBooster(UBoosterPart* NewBooster);
  void SetLeftHandheld(UHandheldPart* NewLeftHandheld);
  void SetRightHandheld(UHandheldPart* NewRightHandheld);
  void SetFirstChip(UChipPart* NewFirstChip);
  void SetSecondChip(UChipPart* NewSecondChip);
  void SetThirdChip(UChipPart* NewThirdChip);

  void SetDefaultAssignment();

  void SetAssignment(UPartAssignment* NewPartAssignment);
  void SetAssignment(FPartAssignmentIDs PartAssignmentIDs);

  FPartAssignmentIDs GetPartAssignmentIDs() const;

  UHeadPart* GetHead() const;
  UCorePart* GetCore() const;
  UArmsPart* GetArms() const;
  ULegsPart* GetLegs() const;
  UBoosterPart* GetBooster() const;
  UHandheldPart* GetLeftHandheld() const;
  UHandheldPart* GetRightHandheld() const;
  UChipPart* GetFirstChip() const;
  UChipPart* GetSecondChip() const;
  UChipPart* GetThirdChip() const;
  
  FNoParamAssignmentChangedDelegate PartAssignmentChangedDelegate;

//TODO: rename
  FAssignmentChangedDelegate HeadAssignedDelegate;
  FAssignmentChangedDelegate CoreAssignedDelegate;
  FAssignmentChangedDelegate ArmsAssignedDelegate;
  FAssignmentChangedDelegate LegsAssignedDelegate;
  FAssignmentChangedDelegate BoosterAssignedDelegate;
  FAssignmentChangedDelegate LeftHandheldAssignedDelegate;
  FAssignmentChangedDelegate RightHandheldAssignedDelegate;
  FAssignmentChangedDelegate FirstChipAssignedDelegate;
  FAssignmentChangedDelegate SecondChipAssignedDelegate;
  FAssignmentChangedDelegate ThirdChipAssignedDelegate;

protected:
  
  UPROPERTY(BlueprintReadOnly)
  UHeadPart* Head;
  UPROPERTY(BlueprintReadOnly)
  UCorePart* Core;
  UPROPERTY(BlueprintReadOnly)
  UArmsPart* Arms;
  UPROPERTY(BlueprintReadOnly)
  ULegsPart* Legs;
  UPROPERTY(BlueprintReadOnly)
  UBoosterPart* Booster;
  UPROPERTY(BlueprintReadOnly)
  UHandheldPart* LeftHandheld;
  UPROPERTY(BlueprintReadOnly)
  UHandheldPart* RightHandheld;
  UPROPERTY(BlueprintReadOnly)
  UChipPart* FirstChip;
  UPROPERTY(BlueprintReadOnly)
  UChipPart* SecondChip;
  UPROPERTY(BlueprintReadOnly)
  UChipPart* ThirdChip;

};
