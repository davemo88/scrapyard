// Fill out your copyright notice in the Description page of Project Settings.

#include "SoloDraft.h"
#include "PartAssignment.h"

USoloDraft::USoloDraft()
{
  PartAssignment = CreateDefaultSubobject<UPartAssignment>(TEXT("PartAssignment"));  
}

void USoloDraft::DraftPart(URobotPart* Part)
{
//TODO: idea - doubles level up a part, so 3 makes rare
  DraftedParts.AddUnique(Part);
}
