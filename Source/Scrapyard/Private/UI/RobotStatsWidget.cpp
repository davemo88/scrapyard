// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotStatsWidget.h"
#include "UI/StatLineWidget.h"

void URobotStatsWidget::NativeConstruct()
{
  HitPointsStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetHitPointsName", "Hit Points"), FText::AsNumber(0)));
  MassStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetMassName", "Mass"), FText::AsNumber(0)));
  PowerSupplyStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetPowerSupplyName", "Power Supply"), FText::AsNumber(0)));
  PowerDrainStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetPowerDrainName", "Power Drain"), FText::AsNumber(0)));
  KineticDefenseStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetKineticDefenseName", "Physical Defense"), FText::AsNumber(0)));
  ElectricDefenseStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetElectricDefenseName", "Energy Defense"), FText::AsNumber(0)));
  TargetingAbilityStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetTargetingAbilityName", "Targeting Ability"), FText::AsNumber(0)));
  ChipSlotsStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetChipSlotsName", "Chip Slots"), FText::AsNumber(0)));
  WeaponDexterityStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetWeaponDexterityName", "Weapon Dexterity"), FText::AsNumber(0)));
  BoosterThrustStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetBoosterThrustName", "Booster Thrust"), FText::AsNumber(0)));
  BoosterPowerDrainStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetBoosterPowerDrainName", "Booster Power Drain"), FText::AsNumber(0)));
  MovementSpeedStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetMovementSpeedName", "Movement Speed"), FText::AsNumber(0)));
}

void URobotStatsWidget::SetRobotStats(URobotStats* NewRobotStats)
{
  RobotStats = NewRobotStats;
  RobotStats->RobotStatsUpdatedDelegate.AddDynamic(this, &URobotStatsWidget::UpdateStats);
  UpdateStats();
}

void URobotStatsWidget::UpdateStats()
{
  MassStatLine->SetStatLine(RobotStats->GetMassStatText());
  HitPointsStatLine->SetStatLine(RobotStats->GetHitPointsStatText());
  PowerDrainStatLine->SetStatLine(RobotStats->GetPowerDrainStatText());
  PowerSupplyStatLine->SetStatLine(RobotStats->GetPowerSupplyStatText());
  KineticDefenseStatLine->SetStatLine(RobotStats->GetKineticDefenseStatText());
  ElectricDefenseStatLine->SetStatLine(RobotStats->GetElectricDefenseStatText());
  TargetingAbilityStatLine->SetStatLine(RobotStats->GetTargetingAbilityStatText());
  ChipSlotsStatLine->SetStatLine(RobotStats->GetChipSlotsStatText());
  WeaponDexterityStatLine->SetStatLine(RobotStats->GetWeaponDexterityStatText());
  BoosterThrustStatLine->SetStatLine(RobotStats->GetBoosterThrustStatText());
  BoosterPowerDrainStatLine->SetStatLine(RobotStats->GetBoosterPowerDrainStatText());
  MovementSpeedStatLine->SetStatLine(RobotStats->GetMovementSpeedStatText());

}

