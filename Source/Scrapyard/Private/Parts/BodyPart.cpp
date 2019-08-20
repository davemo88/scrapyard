// Fill out your copyright notice in the Description page of Project Settings.


#include "BodyPart.h"

TArray<FStatText> UBodyPart::GetStatsText() const
{
  TArray<FStatText> StatsText = Super::GetStatsText();
  StatsText.Add(FStatText(NSLOCTEXT("SY", "HitPointsStatText", "Hit Points"),FText::AsNumber(Mass)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "KineticDefenseStatText", "Kinetic Defense"),FText::AsNumber(KineticDefense)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "ElectricDefenseStatText", "Electric Defense"),FText::AsNumber(ElectricDefense)));
  return StatsText;
}

