// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotStats.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"

void URobotStats::SetPartAssignment(URobotPartAssignment* NewPartAssignment)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetPartAssignment"), *GetName());
  PartAssignment = NewPartAssignment;
  PartAssignment->PartAssignmentChangedDelegate.AddDynamic(this, &URobotStats::UpdateStats);
  UpdateStats();
}

void URobotStats::UpdateStats()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::UpdateStats"), *GetName());

  ZeroStats();

  if (UHeadPart* Head = PartAssignment->GetHead())
  {
    Mass += Head->Mass;
    PowerDrain += Head->PowerDrain;
  }
  if (UCorePart* Core = PartAssignment->GetCore())
  {
    Mass += Core->Mass;
    PowerDrain += Core->PowerDrain;
  }
  if (UArmsPart* Arms = PartAssignment->GetArms())
  {
    Mass += Arms->Mass;
    PowerDrain += Arms->PowerDrain;
  }
  if (ULegsPart* Legs = PartAssignment->GetLegs())
  {
    Mass += Legs->Mass;
    PowerDrain += Legs->PowerDrain;
  }

  RobotStatsUpdatedDelegate.Broadcast();
}

void URobotStats::ZeroStats()
{
  Mass = 0;
  MaxHitPoints = 0;
  MaxPower = 0;
  PhysicalDefense = 0;
  EnergyDefense = 0;
}

TMap<FString, FText> URobotStats::GetRobotStatValues()
{
  TMap<FString, FText> StatValues;
  StatValues.Add(TEXT("Mass"), FText::AsNumber(Mass));
  return StatValues;
}

