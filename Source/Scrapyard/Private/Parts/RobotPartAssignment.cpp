// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotPartAssignment.h"
#include "Parts/Head/HeadPart_Default.h"
#include "Parts/Core/CorePart_Default.h"
#include "Parts/Arms/ArmsPart_Default.h"
#include "Parts/Legs/LegsPart_Default.h"
#include "Parts/RobotPartHelper.h"

bool URobotPartAssignment::IsComplete() const
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

void URobotPartAssignment::SetAssignment(URobotPartAssignment* NewPartAssignment)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetAssignment"), *GetName());
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

void URobotPartAssignment::SetAssignment(FPartAssignmentIDs PartAssignmentIDs)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetFromPartAssignmentIDs"), *GetName());
  TMap<uint32, TSubclassOf<URobotPart>> PartDB = URobotPartHelper::GetPartDatabase();
  UE_LOG(LogTemp, Warning, TEXT("Head PartID: %d"), PartAssignmentIDs.HeadID);
  UE_LOG(LogTemp, Warning, TEXT("Core PartID: %d"), PartAssignmentIDs.CoreID);
  UE_LOG(LogTemp, Warning, TEXT("Arms PartID: %d"), PartAssignmentIDs.ArmsID);
  UE_LOG(LogTemp, Warning, TEXT("Legs PartID: %d"), PartAssignmentIDs.LegsID);
  
  if (TSubclassOf<URobotPart>* NewHeadUClass = PartDB.Find(PartAssignmentIDs.HeadID))
  {
    Head = NewObject<UHeadPart>(this, *NewHeadUClass);
    HeadAssignmentChangedDelegate.Broadcast(Head);
  }
  if (TSubclassOf<URobotPart>* NewCoreUClass = PartDB.Find(PartAssignmentIDs.CoreID))
  {
    Core = NewObject<UCorePart>(this, *NewCoreUClass);
    CoreAssignmentChangedDelegate.Broadcast(Core);
  }
  if (TSubclassOf<URobotPart>* NewArmsUClass = PartDB.Find(PartAssignmentIDs.ArmsID))
  {
    Arms = NewObject<UArmsPart>(this, *NewArmsUClass);
    ArmsAssignmentChangedDelegate.Broadcast(Arms);
  }
  if (TSubclassOf<URobotPart>* NewLegsUClass = PartDB.Find(PartAssignmentIDs.LegsID))
  {
    Legs = NewObject<ULegsPart>(this, *NewLegsUClass);
    LegsAssignmentChangedDelegate.Broadcast(Legs);
  }

  PartAssignmentChangedDelegate.Broadcast();
}

FPartAssignmentIDs URobotPartAssignment::GetPartAssignmentIDs() const
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

UHeadPart* URobotPartAssignment::GetHead() const
{
  return Head;
}

UCorePart* URobotPartAssignment::GetCore() const
{
  return Core;
}

UArmsPart* URobotPartAssignment::GetArms() const
{
  return Arms;
}

ULegsPart* URobotPartAssignment::GetLegs() const
{
  return Legs;
}

