// Fill out your copyright notice in the Description page of Project Settings.


#include "PartAssignment.h"
#include "Game/ScrapyardGameInstance.h"
#include "Parts/RobotPart.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/ChipPart.h"
#include "Parts/HandheldPart.h"

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

void UPartAssignment::SetLeftHandheld(UHandheldPart* NewHandheld)
{
  LeftHandheld = NewHandheld;
  PartAssignmentChangedDelegate.Broadcast();
  LeftHandheldAssignmentChangedDelegate.Broadcast(NewHandheld);
}

void UPartAssignment::SetRightHandheld(UHandheldPart* NewHandheld)
{
  RightHandheld = NewHandheld;
  PartAssignmentChangedDelegate.Broadcast();
  RightHandheldAssignmentChangedDelegate.Broadcast(NewHandheld);
}

void UPartAssignment::SetFirstChip(UChipPart* NewChip)
{
  FirstChip = NewChip;
  PartAssignmentChangedDelegate.Broadcast();
  FirstChipAssignmentChangedDelegate.Broadcast(NewChip);
}

void UPartAssignment::SetSecondChip(UChipPart* NewChip)
{
  SecondChip = NewChip;
  PartAssignmentChangedDelegate.Broadcast();
  SecondChipAssignmentChangedDelegate.Broadcast(NewChip);
}

void UPartAssignment::SetThirdChip(UChipPart* NewChip)
{
  ThirdChip = NewChip;
  PartAssignmentChangedDelegate.Broadcast();
  ThirdChipAssignmentChangedDelegate.Broadcast(NewChip);
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
//      SetLeftHandheld(GameInstance->PartSingleton->PartDB.GetPart<UHandheldPart>(5000));
      SetRightHandheld(GameInstance->PartSingleton->PartDB.GetPart<UHandheldPart>(5000));
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
    LeftHandheld = NewPartAssignment->LeftHandheld;
    RightHandheld = NewPartAssignment->RightHandheld;
    FirstChip = NewPartAssignment->FirstChip;
    SecondChip = NewPartAssignment->SecondChip;
    ThirdChip = NewPartAssignment->ThirdChip;
    HeadAssignmentChangedDelegate.Broadcast(Head);
    CoreAssignmentChangedDelegate.Broadcast(Core);
    ArmsAssignmentChangedDelegate.Broadcast(Arms);
    LegsAssignmentChangedDelegate.Broadcast(Legs);
//TODO: could be null so need to handle that
    LeftHandheldAssignmentChangedDelegate.Broadcast(LeftHandheld);
    RightHandheldAssignmentChangedDelegate.Broadcast(RightHandheld);
    FirstChipAssignmentChangedDelegate.Broadcast(FirstChip);
    SecondChipAssignmentChangedDelegate.Broadcast(SecondChip);
    ThirdChipAssignmentChangedDelegate.Broadcast(ThirdChip);
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
  UE_LOG(LogTemp, Warning, TEXT("Left Handheld PartID: %d"), PartAssignmentIDs.LeftHandheldID);
  UE_LOG(LogTemp, Warning, TEXT("Right Handheld PartID: %d"), PartAssignmentIDs.RightHandheldID);
  UE_LOG(LogTemp, Warning, TEXT("First Chip PartID: %d"), PartAssignmentIDs.FirstChipID);
  UE_LOG(LogTemp, Warning, TEXT("Second Chip PartID: %d"), PartAssignmentIDs.SecondChipID);
  UE_LOG(LogTemp, Warning, TEXT("Third Chip PartID: %d"), PartAssignmentIDs.ThirdChipID);

  if (UScrapyardGameInstance* GameInstance = UScrapyardGameInstance::GameInstance)
  {
    if (UHeadPart* NewHead = GameInstance->PartSingleton->PartDB.GetPart<UHeadPart>(PartAssignmentIDs.HeadID))
    {
      Head = NewHead;
      HeadAssignmentChangedDelegate.Broadcast(Head);
    }
    if (UCorePart* NewCore = GameInstance->PartSingleton->PartDB.GetPart<UCorePart>(PartAssignmentIDs.CoreID))
    {
      Core = NewCore;
      CoreAssignmentChangedDelegate.Broadcast(Core);
    }
    if (UArmsPart* NewArms = GameInstance->PartSingleton->PartDB.GetPart<UArmsPart>(PartAssignmentIDs.ArmsID))
    {
      Arms = NewArms;
      ArmsAssignmentChangedDelegate.Broadcast(Arms);
    }
    if (ULegsPart* NewLegs = GameInstance->PartSingleton->PartDB.GetPart<ULegsPart>(PartAssignmentIDs.LegsID))
    {
      Legs = NewLegs;
      LegsAssignmentChangedDelegate.Broadcast(Legs);
    }
    if (UHandheldPart* NewHandheld = GameInstance->PartSingleton->PartDB.GetPart<UHandheldPart>(PartAssignmentIDs.LeftHandheldID))
    {
      LeftHandheld = NewHandheld;
      LeftHandheldAssignmentChangedDelegate.Broadcast(LeftHandheld);
    }
    if (UHandheldPart* NewHandheld = GameInstance->PartSingleton->PartDB.GetPart<UHandheldPart>(PartAssignmentIDs.RightHandheldID))
    {
      RightHandheld = NewHandheld;
      RightHandheldAssignmentChangedDelegate.Broadcast(RightHandheld);
    }
    if (UChipPart* NewChip = GameInstance->PartSingleton->PartDB.GetPart<UChipPart>(PartAssignmentIDs.FirstChipID))
    {
      FirstChip = NewChip;
      FirstChipAssignmentChangedDelegate.Broadcast(FirstChip);
    }
    if (UChipPart* NewChip = GameInstance->PartSingleton->PartDB.GetPart<UChipPart>(PartAssignmentIDs.SecondChipID))
    {
      SecondChip = NewChip;
      SecondChipAssignmentChangedDelegate.Broadcast(SecondChip);
    }
    if (UChipPart* NewChip = GameInstance->PartSingleton->PartDB.GetPart<UChipPart>(PartAssignmentIDs.ThirdChipID))
    {
      ThirdChip = NewChip;
      ThirdChipAssignmentChangedDelegate.Broadcast(ThirdChip);
    }
  }

  PartAssignmentChangedDelegate.Broadcast();
}

FPartAssignmentIDs UPartAssignment::GetPartAssignmentIDs() const
{
  FPartAssignmentIDs PartAssignmentIDs;

// BUG: this seems like it will cause problems when it will return all 0's for incomplete assignments
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

// TODO: need to do null checks for optional parts, maybe all
    if (LeftHandheld != nullptr)
    {
      PartAssignmentIDs.LeftHandheldID = LeftHandheld->PartID;
    }
    UE_LOG(LogTemp, Warning, TEXT("Left Handheld PartID: %d"), PartAssignmentIDs.LeftHandheldID);
    if (RightHandheld != nullptr)
    {
      PartAssignmentIDs.RightHandheldID = RightHandheld->PartID;
    }
    UE_LOG(LogTemp, Warning, TEXT("Right Handheld PartID: %d"), PartAssignmentIDs.RightHandheldID);
    if (FirstChip != nullptr)
    {
      PartAssignmentIDs.FirstChipID = FirstChip->PartID;
    }
    UE_LOG(LogTemp, Warning, TEXT("First Chip PartID: %d"), PartAssignmentIDs.FirstChipID);
    if (SecondChip != nullptr)
    {
      PartAssignmentIDs.SecondChipID = SecondChip->PartID;
    }
    UE_LOG(LogTemp, Warning, TEXT("Second Chip PartID: %d"), PartAssignmentIDs.SecondChipID);
    if (ThirdChip != nullptr)
    {
      PartAssignmentIDs.ThirdChipID = ThirdChip->PartID;
    }
    UE_LOG(LogTemp, Warning, TEXT("Third Chip PartID: %d"), PartAssignmentIDs.ThirdChipID);
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

UHandheldPart* UPartAssignment::GetLeftHandheld() const
{
  return LeftHandheld;
}

UHandheldPart* UPartAssignment::GetRightHandheld() const
{
  return RightHandheld;
}

UChipPart* UPartAssignment::GetFirstChip() const
{
  return FirstChip;
}

UChipPart* UPartAssignment::GetSecondChip() const
{
  return SecondChip;
}

UChipPart* UPartAssignment::GetThirdChip() const
{
  return ThirdChip;
}

