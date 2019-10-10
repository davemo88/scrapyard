// Fill out your copyright notice in the Description page of Project Settings.


#include "PartAssignment.h"
#include "Scrapyard.h"
#include "Game/ScrapyardGameInstance.h"
#include "Parts/RobotPart.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/BoosterPart.h"
#include "Parts/ChipPart.h"
#include "Parts/HandheldPart.h"

bool UPartAssignment::IsComplete() const
{
  return (Head != nullptr) && (Core != nullptr) && (Arms != nullptr) && (Legs != nullptr);
}

void UPartAssignment::SetHead(UHeadPart* NewHead)
{
  Head = NewHead;
  PartAssignmentChangedDelegate.Broadcast();
  HeadAssignedDelegate.Broadcast(NewHead);
}

void UPartAssignment::SetCore(UCorePart* NewCore)
{
  Core = NewCore;
  PartAssignmentChangedDelegate.Broadcast();
  CoreAssignedDelegate.Broadcast(NewCore);
}

void UPartAssignment::SetArms(UArmsPart* NewArms)
{
  Arms = NewArms;
  PartAssignmentChangedDelegate.Broadcast();
  ArmsAssignedDelegate.Broadcast(NewArms);
}

void UPartAssignment::SetLegs(ULegsPart* NewLegs)
{
  Legs = NewLegs;
  PartAssignmentChangedDelegate.Broadcast();
  LegsAssignedDelegate.Broadcast(NewLegs);
}

void UPartAssignment::SetBooster(UBoosterPart* NewBooster)
{
  Booster = NewBooster;
  PartAssignmentChangedDelegate.Broadcast();
  BoosterAssignedDelegate.Broadcast(NewBooster);
}

void UPartAssignment::SetLeftHandheld(UHandheldPart* NewHandheld)
{
  LeftHandheld = NewHandheld;
  PartAssignmentChangedDelegate.Broadcast();
  LeftHandheldAssignedDelegate.Broadcast(NewHandheld);
}

void UPartAssignment::SetRightHandheld(UHandheldPart* NewHandheld)
{
  RightHandheld = NewHandheld;
  PartAssignmentChangedDelegate.Broadcast();
  RightHandheldAssignedDelegate.Broadcast(NewHandheld);
}

void UPartAssignment::SetFirstChip(UChipPart* NewChip)
{
  FirstChip = NewChip;
  PartAssignmentChangedDelegate.Broadcast();
  FirstChipAssignedDelegate.Broadcast(NewChip);
}

void UPartAssignment::SetSecondChip(UChipPart* NewChip)
{
  SecondChip = NewChip;
  PartAssignmentChangedDelegate.Broadcast();
  SecondChipAssignedDelegate.Broadcast(NewChip);
}

void UPartAssignment::SetThirdChip(UChipPart* NewChip)
{
  ThirdChip = NewChip;
  PartAssignmentChangedDelegate.Broadcast();
  ThirdChipAssignedDelegate.Broadcast(NewChip);
}

void UPartAssignment::SetDefaultAssignment()
{
  if (UScrapyardGameInstance* GameInstance = UScrapyardGameInstance::GameInstance)
  {
//    UE_LOG(LogParts, Log, TEXT("%s::SetDefaultAssignment - GameInstance OK"), *GetName());
    if (GameInstance->PartSingleton != nullptr)
    {
      SetHead(GameInstance->PartSingleton->PartDB.GetPart<UHeadPart>(1000));
      SetCore(GameInstance->PartSingleton->PartDB.GetPart<UCorePart>(2000));
      SetArms(GameInstance->PartSingleton->PartDB.GetPart<UArmsPart>(3000));
      SetLegs(GameInstance->PartSingleton->PartDB.GetPart<ULegsPart>(4000));
      SetBooster(GameInstance->PartSingleton->PartDB.GetPart<UBoosterPart>(5000));
      SetRightHandheld(GameInstance->PartSingleton->PartDB.GetPart<UHandheldPart>(6000));
    }
  }
}

void UPartAssignment::SetAssignment(UPartAssignment* NewPartAssignment)
{
  UE_LOG(LogParts, Log, TEXT("%s::SetAssignment"), *GetName());
// TODO: should be possible with incomplete assignments 
  Head = NewPartAssignment->Head;
  Core = NewPartAssignment->Core;
  Arms = NewPartAssignment->Arms;
  Legs = NewPartAssignment->Legs;
  Booster = NewPartAssignment->Booster;
  LeftHandheld = NewPartAssignment->LeftHandheld;
  RightHandheld = NewPartAssignment->RightHandheld;
  FirstChip = NewPartAssignment->FirstChip;
  SecondChip = NewPartAssignment->SecondChip;
  ThirdChip = NewPartAssignment->ThirdChip;
  HeadAssignedDelegate.Broadcast(Head);
  CoreAssignedDelegate.Broadcast(Core);
  ArmsAssignedDelegate.Broadcast(Arms);
  LegsAssignedDelegate.Broadcast(Legs);
  BoosterAssignedDelegate.Broadcast(Booster);
//TODO: could be null so need to handle that
  LeftHandheldAssignedDelegate.Broadcast(LeftHandheld);
  RightHandheldAssignedDelegate.Broadcast(RightHandheld);
  FirstChipAssignedDelegate.Broadcast(FirstChip);
  SecondChipAssignedDelegate.Broadcast(SecondChip);
  ThirdChipAssignedDelegate.Broadcast(ThirdChip);
  PartAssignmentChangedDelegate.Broadcast();
}

void UPartAssignment::SetAssignment(FPartAssignmentIDs PartAssignmentIDs)
{
  UE_LOG(LogParts, Verbose, TEXT("%s::SetFromPartAssignmentIDs"), *GetName());
  UE_LOG(LogParts, Verbose, TEXT("Head PartID: %d"), PartAssignmentIDs.HeadID);
  UE_LOG(LogParts, Verbose, TEXT("Core PartID: %d"), PartAssignmentIDs.CoreID);
  UE_LOG(LogParts, Verbose, TEXT("Arms PartID: %d"), PartAssignmentIDs.ArmsID);
  UE_LOG(LogParts, Verbose, TEXT("Legs PartID: %d"), PartAssignmentIDs.LegsID);
  UE_LOG(LogParts, Verbose, TEXT("Booster PartID: %d"), PartAssignmentIDs.BoosterID);
  UE_LOG(LogParts, Verbose, TEXT("Left Handheld PartID: %d"), PartAssignmentIDs.LeftHandheldID);
  UE_LOG(LogParts, Verbose, TEXT("Right Handheld PartID: %d"), PartAssignmentIDs.RightHandheldID);
  UE_LOG(LogParts, Verbose, TEXT("First Chip PartID: %d"), PartAssignmentIDs.FirstChipID);
  UE_LOG(LogParts, Verbose, TEXT("Second Chip PartID: %d"), PartAssignmentIDs.SecondChipID);
  UE_LOG(LogParts, Verbose, TEXT("Third Chip PartID: %d"), PartAssignmentIDs.ThirdChipID);

  if (UScrapyardGameInstance* GameInstance = UScrapyardGameInstance::GameInstance)
  {
    if (UHeadPart* NewHead = GameInstance->PartSingleton->PartDB.GetPart<UHeadPart>(PartAssignmentIDs.HeadID))
    {
      Head = NewHead;
      HeadAssignedDelegate.Broadcast(Head);
    }
    if (UCorePart* NewCore = GameInstance->PartSingleton->PartDB.GetPart<UCorePart>(PartAssignmentIDs.CoreID))
    {
      Core = NewCore;
      CoreAssignedDelegate.Broadcast(Core);
    }
    if (UArmsPart* NewArms = GameInstance->PartSingleton->PartDB.GetPart<UArmsPart>(PartAssignmentIDs.ArmsID))
    {
      Arms = NewArms;
      ArmsAssignedDelegate.Broadcast(Arms);
    }
    if (ULegsPart* NewLegs = GameInstance->PartSingleton->PartDB.GetPart<ULegsPart>(PartAssignmentIDs.LegsID))
    {
      Legs = NewLegs;
      LegsAssignedDelegate.Broadcast(Legs);
    }
    if (UBoosterPart* NewBooster = GameInstance->PartSingleton->PartDB.GetPart<UBoosterPart>(PartAssignmentIDs.BoosterID))
    {
      Booster = NewBooster;
      BoosterAssignedDelegate.Broadcast(Booster);
    }
    if (UHandheldPart* NewHandheld = GameInstance->PartSingleton->PartDB.GetPart<UHandheldPart>(PartAssignmentIDs.LeftHandheldID))
    {
      LeftHandheld = NewHandheld;
      LeftHandheldAssignedDelegate.Broadcast(LeftHandheld);
    }
    if (UHandheldPart* NewHandheld = GameInstance->PartSingleton->PartDB.GetPart<UHandheldPart>(PartAssignmentIDs.RightHandheldID))
    {
      RightHandheld = NewHandheld;
      RightHandheldAssignedDelegate.Broadcast(RightHandheld);
    }
    if (UChipPart* NewChip = GameInstance->PartSingleton->PartDB.GetPart<UChipPart>(PartAssignmentIDs.FirstChipID))
    {
      FirstChip = NewChip;
      FirstChipAssignedDelegate.Broadcast(FirstChip);
    }
    if (UChipPart* NewChip = GameInstance->PartSingleton->PartDB.GetPart<UChipPart>(PartAssignmentIDs.SecondChipID))
    {
      SecondChip = NewChip;
      SecondChipAssignedDelegate.Broadcast(SecondChip);
    }
    if (UChipPart* NewChip = GameInstance->PartSingleton->PartDB.GetPart<UChipPart>(PartAssignmentIDs.ThirdChipID))
    {
      ThirdChip = NewChip;
      ThirdChipAssignedDelegate.Broadcast(ThirdChip);
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
    UE_LOG(LogParts, Log, TEXT("Head PartID: %d"), PartAssignmentIDs.HeadID);
    PartAssignmentIDs.CoreID = Core->PartID;
    UE_LOG(LogParts, Log, TEXT("Core PartID: %d"), PartAssignmentIDs.CoreID);
    PartAssignmentIDs.ArmsID = Arms->PartID;
    UE_LOG(LogParts, Log, TEXT("Arms PartID: %d"), PartAssignmentIDs.ArmsID);
    PartAssignmentIDs.LegsID = Legs->PartID;
    UE_LOG(LogParts, Log, TEXT("Legs PartID: %d"), PartAssignmentIDs.LegsID);
    PartAssignmentIDs.BoosterID = Booster->PartID;
    UE_LOG(LogParts, Log, TEXT("Booster PartID: %d"), PartAssignmentIDs.BoosterID);

// TODO: need to do null checks for optional parts, maybe all
    if (LeftHandheld != nullptr)
    {
      PartAssignmentIDs.LeftHandheldID = LeftHandheld->PartID;
    }
    UE_LOG(LogParts, Log, TEXT("Left Handheld PartID: %d"), PartAssignmentIDs.LeftHandheldID);
    if (RightHandheld != nullptr)
    {
      PartAssignmentIDs.RightHandheldID = RightHandheld->PartID;
    }
    UE_LOG(LogParts, Log, TEXT("Right Handheld PartID: %d"), PartAssignmentIDs.RightHandheldID);
    if (FirstChip != nullptr)
    {
      PartAssignmentIDs.FirstChipID = FirstChip->PartID;
    }
    UE_LOG(LogParts, Log, TEXT("First Chip PartID: %d"), PartAssignmentIDs.FirstChipID);
    if (SecondChip != nullptr)
    {
      PartAssignmentIDs.SecondChipID = SecondChip->PartID;
    }
    UE_LOG(LogParts, Log, TEXT("Second Chip PartID: %d"), PartAssignmentIDs.SecondChipID);
    if (ThirdChip != nullptr)
    {
      PartAssignmentIDs.ThirdChipID = ThirdChip->PartID;
    }
    UE_LOG(LogParts, Log, TEXT("Third Chip PartID: %d"), PartAssignmentIDs.ThirdChipID);
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

UBoosterPart* UPartAssignment::GetBooster() const
{
  return Booster;
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

