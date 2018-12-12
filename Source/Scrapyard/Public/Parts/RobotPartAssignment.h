// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RobotPartAssignment.generated.h"

class UHeadPart;
class UCorePart;
class UArmsPart;
class ULegsPart;

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
class SCRAPYARD_API URobotPartAssignment : public UObject
{
  GENERATED_BODY()

protected:
  
  UPROPERTY(BlueprintReadOnly)
  UHeadPart* Head;
  UPROPERTY(BlueprintReadOnly)
  UCorePart* Core;
  UPROPERTY(BlueprintReadOnly)
  UArmsPart* Arms;
  UPROPERTY(BlueprintReadOnly)
  ULegsPart* Legs;

public:

  bool IsComplete();

  void SetHead(UHeadPart* NewHead);
  void SetCore(UCorePart* NewCore);
  void SetArms(UArmsPart* NewArms);
  void SetLegs(ULegsPart* NewLegs);

  void SetDefaultAssignment();

  void CopyAssignment(URobotPartAssignment* NewPartAssignment);

  UHeadPart* GetHead();
  UCorePart* GetCore();
  UArmsPart* GetArms();
  ULegsPart* GetLegs();
  
  FPartAssignmentChangedDelegate PartAssignmentChangedDelegate;
  FHeadAssignmentChangedDelegate HeadAssignmentChangedDelegate;
  FCoreAssignmentChangedDelegate CoreAssignmentChangedDelegate;
  FArmsAssignmentChangedDelegate ArmsAssignmentChangedDelegate;
  FLegsAssignmentChangedDelegate LegsAssignmentChangedDelegate;

  
};
