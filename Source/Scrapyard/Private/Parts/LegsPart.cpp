// Fill out your copyright notice in the Description page of Project Settings.

#include "LegsPart.h"
#include "SoloDraft.h"

void ULegsPart::Draft(USoloDraft* SoloDraft)
{
	SoloDraft->DraftedLegs.AddUnique(this);
}

