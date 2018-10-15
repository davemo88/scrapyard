// Fill out your copyright notice in the Description page of Project Settings.


#include "SoloDraftGameState.h"
#include "SoloDraft.h"

ASoloDraftGameState::ASoloDraftGameState()
{
  CurrentDraft = CreateDefaultSubobject<USoloDraft>(TEXT("CurrentDraft"));
}


