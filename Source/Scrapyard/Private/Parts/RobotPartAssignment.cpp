// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotPartAssignment.h"
#include "Parts/Head/HeadPart_Default.h"
#include "Parts/Core/CorePart_Default.h"
#include "Parts/Arms/ArmsPart_Default.h"
#include "Parts/Legs/LegsPart_Default.h"

bool URobotPartAssignment::IsComplete()
{
  return (Head != NULL) && (Core != NULL) && (Arms != NULL) && (Legs != NULL);
}

void URobotPartAssignment::SetHead(UHeadPart* NewHead)
{
  Head = NewHead;
  PartAssignmentChangedDelegate.Broadcast();
  HeadAssignmentChangedDelegate.Broadcast(NewHead);
}

void URobotPartAssignment::SetCore(UCorePart* NewCore)
{
  Core = NewCore;
  PartAssignmentChangedDelegate.Broadcast();
  CoreAssignmentChangedDelegate.Broadcast(NewCore);
}

void URobotPartAssignment::SetArms(UArmsPart* NewArms)
{
  Arms = NewArms;
  PartAssignmentChangedDelegate.Broadcast();
  ArmsAssignmentChangedDelegate.Broadcast(NewArms);
}

void URobotPartAssignment::SetLegs(ULegsPart* NewLegs)
{
  Legs = NewLegs;
  PartAssignmentChangedDelegate.Broadcast();
  LegsAssignmentChangedDelegate.Broadcast(NewLegs);
}

void URobotPartAssignment::SetDefaultAssignment()
{
  SetHead(NewObject<UHeadPart_Default>());
  SetCore(NewObject<UCorePart_Default>());
  SetArms(NewObject<UArmsPart_Default>());
  SetLegs(NewObject<ULegsPart_Default>());
}

void URobotPartAssignment::CopyAssignment(URobotPartAssignment* NewPartAssignment)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::CopyAssignment"), *GetName());
  if (NewPartAssignment->IsComplete())
  {
// TODO: unsafe with incomplete assignments but should be possible
    Head = NewPartAssignment->Head;
    Core = NewPartAssignment->Core;
    Arms = NewPartAssignment->Arms;
    Legs = NewPartAssignment->Legs;
    HeadAssignmentChangedDelegate.Broadcast(Head);
    CoreAssignmentChangedDelegate.Broadcast(Core);
    ArmsAssignmentChangedDelegate.Broadcast(Arms);
    LegsAssignmentChangedDelegate.Broadcast(Legs);
    PartAssignmentChangedDelegate.Broadcast();
  }
}

FPartAssignmentIDs URobotPartAssignment::GetPartAssignmentIDs()
{
  FPartAssignmentIDs PartAssignmentIDs;

  if (IsComplete())
  {
    PartAssignmentIDs.HeadID = Head->GetPartID();
    UE_LOG(LogTemp, Warning, TEXT("Head PartID: %d"), PartAssignmentIDs.HeadID);
    PartAssignmentIDs.CoreID = Core->GetPartID();
    UE_LOG(LogTemp, Warning, TEXT("Core PartID: %d"), PartAssignmentIDs.CoreID);
    PartAssignmentIDs.ArmsID = Arms->GetPartID();
    UE_LOG(LogTemp, Warning, TEXT("Arms PartID: %d"), PartAssignmentIDs.ArmsID);
    PartAssignmentIDs.LegsID = Legs->GetPartID();
    UE_LOG(LogTemp, Warning, TEXT("Legs PartID: %d"), PartAssignmentIDs.LegsID);
  }

  return PartAssignmentIDs;
}

UHeadPart* URobotPartAssignment::GetHead()
{
  return Head;
}

UCorePart* URobotPartAssignment::GetCore()
{
  return Core;
}

UArmsPart* URobotPartAssignment::GetArms()
{
  return Arms;
}

ULegsPart* URobotPartAssignment::GetLegs()
{
  return Legs;
}

