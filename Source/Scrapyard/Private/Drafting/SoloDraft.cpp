// Fill out your copyright notice in the Description page of Project Settings.

#include "SoloDraft.h"
#include "Game/ScrapyardGameInstance.h"
#include "Parts/PartAssignment.h"
#include "Parts/PartSingleton.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/BoosterPart.h"
#include "Parts/ChipPart.h"
#include "Parts/HandheldPart.h"

USoloDraft::USoloDraft()
{
  PartAssignment = CreateDefaultSubobject<UPartAssignment>(TEXT("PartAssignment"));  
  PartAssignment->SetDefaultAssignment();
}

void USoloDraft::DraftPart(URobotPart* Part)
{
//TODO: idea - doubles level up a part, so 3 makes rare ala autochess
  DraftedParts.AddUnique(Part);
}
