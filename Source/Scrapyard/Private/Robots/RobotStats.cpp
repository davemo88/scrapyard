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
    Armor += Head->Armor;
    EMShield += Head->EMShield;
    PowerDrain += Head->PowerDrain;
    TargetingAbility = Head->TargetingAbility;
    ChipSlots = Head->ChipSlots;
  }
  if (UCorePart* Core = PartAssignment->GetCore())
  {
    Mass += Core->Mass;
    HitPoints += Core->HitPoints;
    Armor += Core->Armor;
    EMShield += Core->EMShield;
    PowerDrain += Core->PowerDrain;
    PowerSupply = Core->PowerSupply;
  }
  if (UArmsPart* Arms = PartAssignment->GetArms())
  {
    Mass += Arms->Mass;
    HitPoints += Arms->HitPoints;
    Armor += Arms->Armor;
    EMShield += Arms->EMShield;
    PowerDrain += Arms->PowerDrain;
    WeaponDexterity = Arms->WeaponDexterity;
  }
  if (ULegsPart* Legs = PartAssignment->GetLegs())
  {
    Mass += Legs->Mass;
    HitPoints += Legs->HitPoints;
    Armor += Legs->Armor;
    EMShield += Legs->EMShield;
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
  Mass = 0;
  HitPoints = 0;
  MaxPower = 0;
  PowerSupply = 0;
  PowerDrain = 0;
  Armor = 0;
  EMShield = 0;
  BoosterThrust = 0;
  BoosterPowerDrain = 0;
  MovementSpeed = 0;
  WeaponDexterity = 0;
  TargetingAbility = 0;
  ChipSlots = 0;
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

FStatText URobotStats::GetArmorStatText()
{
  return FStatText(NSLOCTEXT("SY", "StatWidgetArmorName", "Armor"), FText::AsNumber(Armor));
}

FStatText URobotStats::GetEMShieldStatText()
{
  return FStatText(NSLOCTEXT("SY", "StatWidgetEMShieldName", "EM Shield"), FText::AsNumber(EMShield));
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


