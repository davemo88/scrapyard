// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotStatsWidget.h"
#include "StatLineWidget.h"

void URobotStatsWidget::NativeConstruct()
{
  HitPointsStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetHitPointsName", "Hit Points"), FText::AsNumber(0)));
  MassStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetMassName", "Mass"), FText::AsNumber(0)));
  PowerSupplyStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetPowerSupplyName", "Power Supply"), FText::AsNumber(0)));
  PowerDrainStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetPowerDrainName", "Power Drain"), FText::AsNumber(0)));
  PhysicalDefenseStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetPhysicalDefenseName", "Physical Defense"), FText::AsNumber(0)));
  EnergyDefenseStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetEnergyDefenseName", "Energy Defense"), FText::AsNumber(0)));
  TargetingAbilityStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetTargetingAbilityName", "Targeting Ability"), FText::AsNumber(0)));
  WeaponDexterityStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetWeaponDexterityName", "Weapon Dexterity"), FText::AsNumber(0)));
  BoosterThrustStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetBoosterThrustName", "Booster Thrust"), FText::AsNumber(0)));
  MovementSpeedStatLine->SetStatLine(FStatText(NSLOCTEXT("SY", "StatWidgetMovementSpeedName", "Movement Speed"), FText::AsNumber(0)));
}

void URobotStatsWidget::SetRobotStats(URobotStats* NewRobotStats)
{
  RobotStats = NewRobotStats;
  RobotStats->RobotStatsUpdatedDelegate.AddDynamic(this, &URobotStatsWidget::UpdateStats);
}

void URobotStatsWidget::UpdateStats()
{
  MassStatLine->SetStatLine(RobotStats->GetMassStatText());
  HitPointsStatLine->SetStatLine(RobotStats->GetHitPointsStatText());
  PowerDrainStatLine->SetStatLine(RobotStats->GetPowerDrainStatText());
  PowerSupplyStatLine->SetStatLine(RobotStats->GetPowerSupplyStatText());
  PhysicalDefenseStatLine->SetStatLine(RobotStats->GetPhysicalDefenseStatText());
  EnergyDefenseStatLine->SetStatLine(RobotStats->GetEnergyDefenseStatText());
  TargetingAbilityStatLine->SetStatLine(RobotStats->GetTargetingAbilityStatText());
  WeaponDexterityStatLine->SetStatLine(RobotStats->GetWeaponDexterityStatText());
  BoosterThrustStatLine->SetStatLine(RobotStats->GetBoosterThrustStatText());
  MovementSpeedStatLine->SetStatLine(RobotStats->GetMovementSpeedStatText());

}

