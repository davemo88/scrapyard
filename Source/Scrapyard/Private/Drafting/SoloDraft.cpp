// Fill out your copyright notice in the Description page of Project Settings.

#include "SoloDraft.h"
#include "PartAssignment.h"

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
