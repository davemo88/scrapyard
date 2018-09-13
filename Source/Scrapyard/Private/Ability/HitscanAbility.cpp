// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanAbility.h"

UHitscanAbility::UHitscanAbility()
{
  AbilityName = TEXT("HitscanAbility");
}

void UHitscanAbility::FireShot()
{
  UE_LOG(LogTemp, Warning, TEXT("UHitscanAbility::FireShot"));
}
