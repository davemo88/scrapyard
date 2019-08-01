// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotStats.h"
#include "Scrapyard.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/BoosterPart.h"

void URobotStats::SetPartAssignment(UPartAssignment* NewPartAssignment)
{
  UE_LOG(LogParts, Log, TEXT("%s::SetPartAssignment"), *GetName());
  PartAssignment = NewPartAssignment;
  PartAssignment->PartAssignmentChangedDelegate.AddDynamic(this, &URobotStats::UpdateStats);
  UpdateStats();
}

void URobotStats::UpdateStats()
{
  UE_LOG(LogParts, Log, TEXT("%s::UpdateStats"), *GetName());

  ZeroStats();

  if (UHeadPart* Head = PartAssignment->GetHead())
  {
    Mass += Head->Mass;
    HitPoints += Head->HitPoints;
    KineticDefense += Head->KineticDefense;
    ElectricDefense += Head->ElectricDefense;
    PowerDrain += Head->PowerDrain;
    TargetingAbility = Head->TargetingAbility;
    ChipSlots = Head->ChipSlots;
  }
  if (UCorePart* Core = PartAssignment->GetCore())
  {
    Mass += Core->Mass;
    HitPoints += Core->HitPoints;
    KineticDefense += Core->KineticDefense;
    ElectricDefense += Core->ElectricDefense;
    PowerDrain += Core->PowerDrain;
    PowerSupply = Core->PowerSupply;
  }
  if (UArmsPart* Arms = PartAssignment->GetArms())
  {
    Mass += Arms->Mass;
    HitPoints += Arms->HitPoints;
    KineticDefense += Arms->KineticDefense;
    ElectricDefense += Arms->ElectricDefense;
    PowerDrain += Arms->PowerDrain;
    WeaponDexterity = Arms->WeaponDexterity;
  }
  if (ULegsPart* Legs = PartAssignment->GetLegs())
  {
    Mass += Legs->Mass;
    HitPoints += Legs->HitPoints;
    KineticDefense += Legs->KineticDefense;
    ElectricDefense += Legs->ElectricDefense;
    PowerDrain += Legs->PowerDrain;
    MovementSpeed = Legs->MovementSpeed;
  }
  if (UBoosterPart* Booster = PartAssignment->GetBooster())
  {
    Mass += Booster->Mass;
    BoosterThrust = Booster->Thrust;
    BoosterPowerDrain = Booster->ThrustPowerConsumption;
  }


  MaxPower = PowerSupply - PowerDrain;

  RobotStatsUpdatedDelegate.Broadcast();
}

void URobotStats::ZeroStats()
{
// TODO: zero them all
  Mass = 0;
  HitPoints = 0;
  MaxPower = 0;
  PowerSupply = 0;
  PowerDrain = 0;
  KineticDefense = 0;
  ElectricDefense = 0;
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

FStatText URobotStats::GetKineticDefenseStatText()
{
  return FStatText(NSLOCTEXT("SY", "StatWidgetKineticDefenseName", "Kinetic Defense"), FText::AsNumber(KineticDefense));
}

FStatText URobotStats::GetElectricDefenseStatText()
{
  return FStatText(NSLOCTEXT("SY", "StatWidgetElectricDefenseName", "Electric Defense"), FText::AsNumber(ElectricDefense));
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


