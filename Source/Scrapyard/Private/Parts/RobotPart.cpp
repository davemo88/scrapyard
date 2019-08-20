// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPart.h"

TArray<FStatText> URobotPart::GetStatsText() const
{
  TArray<FStatText> StatsText;
  StatsText.Add(FStatText(NSLOCTEXT("SY", "MassStatText", "Mass"),FText::AsNumber(Mass)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "PowerDrainStatText", "Power Drain"),FText::AsNumber(PowerDrain)));
  return StatsText;
}

bool URobotPart::IsDefaultPart()
{
// default parts have IDs divisible by 1000
  return (PartID % 1000) == 0;
}
