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
    HitPoints += Head->HitPoints;
    PhysicalDefense += Head->PhysicalDefense;
    EnergyDefense += Head->EnergyDefense;
    PowerDrain += Head->PowerDrain;
    TargetingAbility = Head->TargetingAbility;
    ChipSlots = Head->ChipSlots;
  }
  if (UCorePart* Core = PartAssignment->GetCore())
  {
    Mass += Core->Mass;
    HitPoints += Core->HitPoints;
    PhysicalDefense += Core->PhysicalDefense;
    EnergyDefense += Core->EnergyDefense;
    PowerDrain += Core->PowerDrain;
    PowerSupply = Core->PowerSupply;
    BoosterThrust = Core->BoosterThrust;
    BoosterPowerDrain = Core->BoosterPowerDrain;

  }
  if (UArmsPart* Arms = PartAssignment->GetArms())
  {
    Mass += Arms->Mass;
    HitPoints += Arms->HitPoints;
    PhysicalDefense += Arms->PhysicalDefense;
    EnergyDefense += Arms->EnergyDefense;
    PowerDrain += Arms->PowerDrain;
    WeaponDexterity = Arms->WeaponDexterity;
  }
  if (ULegsPart* Legs = PartAssignment->GetLegs())
  {
    Mass += Legs->Mass;
    HitPoints += Legs->HitPoints;
    PhysicalDefense += Legs->PhysicalDefense;
    EnergyDefense += Legs->EnergyDefense;
    PowerDrain += Legs->PowerDrain;
    MovementSpeed = Legs->MovementSpeed;
  }

  RobotStatsUpdatedDelegate.Broadcast();
}

void URobotStats::ZeroStats()
{
// TODO: zero them all
  Mass = 0;
  HitPoints = 0;
  MaxPower = 0;
  PowerDrain = 0;
  PhysicalDefense = 0;
  EnergyDefense = 0;
}

FStatText URobotStats::GetHitPointsStatText()
{
  return FStatText(NSLOCTEXT("SY", "StatWidgetHitPointsName", "Hit Points"), FText::AsNumber(HitPoints));
}

FStatText URobotStats::GetMassStatText()
{
  return FStatText(NSLOCTEXT("SY", "StatWidgetMassName", "Mass"), FText::AsNumber(Mass));
}

FStatText URobotStats::GetMaxPowerStatText()
{
  return FStatText(NSLOCTEXT("SY", "StatWidgetMaxPowerName", "Power Supply"), FText::AsNumber(MaxPower));
}

FStatText URobotStats::GetPowerDrainStatText()
{
  return FStatText(NSLOCTEXT("SY", "StatWidgetPowerDrainName", "Power Drain"), FText::AsNumber(PowerDrain));
}

FStatText URobotStats::GetPhysicalDefenseStatText()
{
  return FStatText(NSLOCTEXT("SY", "StatWidgetPhysicalDefenseName", "Physical Defense"), FText::AsNumber(PhysicalDefense));
}

FStatText URobotStats::GetEnergyDefenseStatText()
{
  return FStatText(NSLOCTEXT("SY", "StatWidgetEnergyDefenseName", "Energy Defense"), FText::AsNumber(EnergyDefense));
}

FStatText URobotStats::GetTargetingAbilityStatText()
{
  return FStatText(NSLOCTEXT("SY", "StatWidgetTargetingAbilityName", "Targeting Ability"), FText::AsNumber(TargetingAbility));
}

FStatText URobotStats::GetChipSlotsStatText()
{
  return FStatText(NSLOCTEXT("SY", "StatWidgetChipSlotsName", "Chip Slots"), FText::AsNumber(ChipSlots));
}

FStatText URobotStats::GetWeaponDexterityStatText()
{
  return FStatText(NSLOCTEXT("SY", "StatWidgetWeaponDexterityName", "Weapon Dexterity"), FText::AsNumber(WeaponDexterity));
}

FStatText URobotStats::GetPowerSupplyStatText()
{
  return FStatText(NSLOCTEXT("SY", "StatWidgetPowerSupplyName", "Power Supply"), FText::AsNumber(PowerSupply));
}

FStatText URobotStats::GetBoosterThrustStatText()
{
  return FStatText(NSLOCTEXT("SY", "StatWidgetBoosterThrustName", "Booster Thrust"), FText::AsNumber(BoosterThrust));
}

FStatText URobotStats::GetBoosterPowerDrainStatText()
{
  return FStatText(NSLOCTEXT("SY", "StatWidgetBoosterPowerDrainName", "Booster Power Drain"), FText::AsNumber(BoosterPowerDrain));
}

FStatText URobotStats::GetMovementSpeedStatText()
{
  return FStatText(NSLOCTEXT("SY", "StatWidgetMovementSpeedName", "Movement Speed"), FText::AsNumber(MovementSpeed));
}


