// Fill out your copyright notice in the Description page of Project Settings.

#include "HandheldPart.h"
#include "Ability/ScrapyardAbility.h"
#include "Ability/HitscanAbility.h"
#include "SoloDraft.h"

UHandheldPart::UHandheldPart()
{
  UE_LOG(LogTemp, Warning, TEXT("UHandheldPart:UHandheldPart"));
  PartAbililty = CreateDefaultSubobject<UHitscanAbility>(TEXT("HitscanAbility"));
}

void UHandheldPart::Draft(USoloDraft* SoloDraft)
{
//  SoloDraft->DraftedHandheld.Add(this);
}




