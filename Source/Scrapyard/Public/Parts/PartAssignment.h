// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PartAssignment.generated.h"

class UHeadPart;
class UCorePart;
class UArmsPart;
class ULegsPart;

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

//  bool IsComplete()
//  {
//    return HeadID != 0 && CoreID != 0 && ArmsID != 0 && LegsID != 0;
//  }
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPartAssignmentChangedDelegate);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHeadAssignmentChangedDelegate, UHeadPart*, NewHead);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCoreAssignmentChangedDelegate, UCorePart*, NewCore);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FArmsAssignmentChangedDelegate, UArmsPart*, NewArms);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLegsAssignmentChangedDelegate, ULegsPart*, NewLegs);
// possible to clean this up?
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHeadAssignmentChangedDelegate, URobotPart*, NewHead);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCoreAssignmentChangedDelegate, URobotPart*, NewCore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FArmsAssignmentChangedDelegate, URobotPart*, NewArms);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLegsAssignmentChangedDelegate, URobotPart*, NewLegs);
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

  void SetDefaultAssignment();

  void SetAssignment(UPartAssignment* NewPartAssignment);
  void SetAssignment(FPartAssignmentIDs PartAssignmentIDs);

  FPartAssignmentIDs GetPartAssignmentIDs() const;

  UHeadPart* GetHead() const;
  UCorePart* GetCore() const;
  UArmsPart* GetArms() const;
  ULegsPart* GetLegs() const;
  
  FPartAssignmentChangedDelegate PartAssignmentChangedDelegate;
  FHeadAssignmentChangedDelegate HeadAssignmentChangedDelegate;
  FCoreAssignmentChangedDelegate CoreAssignmentChangedDelegate;
  FArmsAssignmentChangedDelegate ArmsAssignmentChangedDelegate;
  FLegsAssignmentChangedDelegate LegsAssignmentChangedDelegate;

protected:
  
  UPROPERTY(BlueprintReadOnly)
  UHeadPart* Head;
  UPROPERTY(BlueprintReadOnly)
  UCorePart* Core;
  UPROPERTY(BlueprintReadOnly)
  UArmsPart* Arms;
  UPROPERTY(BlueprintReadOnly)
  ULegsPart* Legs;

  void SavePartAssignment();

};
