// Fill out your copyright notice in the Description page of Project Settings.


#include "BodyPart.h"

TArray<FStatText> UBodyPart::GetStatsText() const
{
  TArray<FStatText> StatsText = Super::GetStatsText();
  StatsText.Add(FStatText(NSLOCTEXT("SY", "HitPointsStatText", "Hit Points"),FText::AsNumber(Mass)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "ArmorStatText", "Armor"),FText::AsNumber(Armor)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "EMShieldStatText", "EM Shield"),FText::AsNumber(EMShield)));
  return StatsText;
}

