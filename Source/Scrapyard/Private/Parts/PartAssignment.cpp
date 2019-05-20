// Fill out your copyright notice in the Description page of Project Settings.


#include "PartAssignment.h"
#include "Game/ScrapyardGameInstance.h"
#include "Parts/RobotPart.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"

bool UPartAssignment::IsComplete() const
{
  return (Head != NULL) && (Core != NULL) && (Arms != NULL) && (Legs != NULL);
}

void UPartAssignment::SetHead(UHeadPart* NewHead)
{
  Head = NewHead;
  PartAssignmentChangedDelegate.Broadcast();
  HeadAssignmentChangedDelegate.Broadcast(NewHead);
}

void UPartAssignment::SetCore(UCorePart* NewCore)
{
  Core = NewCore;
  PartAssignmentChangedDelegate.Broadcast();
  CoreAssignmentChangedDelegate.Broadcast(NewCore);
}

void UPartAssignment::SetArms(UArmsPart* NewArms)
{
  Arms = NewArms;
  PartAssignmentChangedDelegate.Broadcast();
  ArmsAssignmentChangedDelegate.Broadcast(NewArms);
}

void UPartAssignment::SetLegs(ULegsPart* NewLegs)
{
  Legs = NewLegs;
  PartAssignmentChangedDelegate.Broadcast();
  LegsAssignmentChangedDelegate.Broadcast(NewLegs);
}

void UPartAssignment::SetDefaultAssignment()
{
  if (UScrapyardGameInstance* GameInstance = UScrapyardGameInstance::GameInstance)
  {
    UE_LOG(LogTemp, Warning, TEXT("%s::SetDefaultAssignment - GameInstance OK"), *GetName());
    if (GameInstance->PartSingleton != nullptr)
    {
      SetHead(GameInstance->PartSingleton->PartDB.GetPart<UHeadPart>(1000));
      SetCore(GameInstance->PartSingleton->PartDB.GetPart<UCorePart>(2000));
      SetArms(GameInstance->PartSingleton->PartDB.GetPart<UArmsPart>(3000));
      SetLegs(GameInstance->PartSingleton->PartDB.GetPart<ULegsPart>(4000));
    }
  }
}

void UPartAssignment::SetAssignment(UPartAssignment* NewPartAssignment)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetAssignment"), *GetName());
// TODO: should be possible with incomplete assignments 
  if (NewPartAssignment->IsComplete())
  {
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

void UPartAssignment::SetAssignment(FPartAssignmentIDs PartAssignmentIDs)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetFromPartAssignmentIDs"), *GetName());
  UE_LOG(LogTemp, Warning, TEXT("Head PartID: %d"), PartAssignmentIDs.HeadID);
  UE_LOG(LogTemp, Warning, TEXT("Core PartID: %d"), PartAssignmentIDs.CoreID);
  UE_LOG(LogTemp, Warning, TEXT("Arms PartID: %d"), PartAssignmentIDs.ArmsID);
  UE_LOG(LogTemp, Warning, TEXT("Legs PartID: %d"), PartAssignmentIDs.LegsID);

//  if (UHeadPart* NewHead = URobotPart::PartDB.GetPart<UHeadPart>(PartAssignmentIDs.HeadID))
//  {
//    Head = NewHead;
//    HeadAssignmentChangedDelegate.Broadcast(Head);
//  }
//  if (UCorePart* NewCore = URobotPart::PartDB.GetPart<UCorePart>(PartAssignmentIDs.CoreID))
//  {
//    Core = NewCore;
//    CoreAssignmentChangedDelegate.Broadcast(Core);
//  }
//  if (UArmsPart* NewArms = URobotPart::PartDB.GetPart<UArmsPart>(PartAssignmentIDs.ArmsID))
//  {
//    Arms = NewArms;
//    ArmsAssignmentChangedDelegate.Broadcast(Arms);
//  }
//  if (ULegsPart* NewLegs = URobotPart::PartDB.GetPart<ULegsPart>(PartAssignmentIDs.LegsID))
//  {
//    Legs = NewLegs;
//    LegsAssignmentChangedDelegate.Broadcast(Legs);
//  }

  PartAssignmentChangedDelegate.Broadcast();
}

FPartAssignmentIDs UPartAssignment::GetPartAssignmentIDs() const
{
  FPartAssignmentIDs PartAssignmentIDs;

  if (IsComplete())
  {
    PartAssignmentIDs.HeadID = Head->PartID;
    UE_LOG(LogTemp, Warning, TEXT("Head PartID: %d"), PartAssignmentIDs.HeadID);
    PartAssignmentIDs.CoreID = Core->PartID;
    UE_LOG(LogTemp, Warning, TEXT("Core PartID: %d"), PartAssignmentIDs.CoreID);
    PartAssignmentIDs.ArmsID = Arms->PartID;
    UE_LOG(LogTemp, Warning, TEXT("Arms PartID: %d"), PartAssignmentIDs.ArmsID);
    PartAssignmentIDs.LegsID = Legs->PartID;
    UE_LOG(LogTemp, Warning, TEXT("Legs PartID: %d"), PartAssignmentIDs.LegsID);
  }

  return PartAssignmentIDs;
}

UHeadPart* UPartAssignment::GetHead() const
{
  return Head;
}

UCorePart* UPartAssignment::GetCore() const
{
  return Core;
}

UArmsPart* UPartAssignment::GetArms() const
{
  return Arms;
}

ULegsPart* UPartAssignment::GetLegs() const
{
  return Legs;
}

