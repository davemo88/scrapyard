// Fill out your copyright notice in the Description page of Project Settings.

#include "HandheldPart.h"
#include "Abilities/ScrapyardAbility.h"
#include "Abilities/HitscanAbility.h"
#include "SoloDraft.h"

UHandheldPart::UHandheldPart()
{
  UE_LOG(LogTemp, Warning, TEXT("UHandheldPart:UHandheldPart"));
  AbilityClass = AHitscanAbility::StaticClass();
}

void UHandheldPart::Draft(USoloDraft* SoloDraft)
{
//  SoloDraft->DraftedHandheld.Add(this);
}




