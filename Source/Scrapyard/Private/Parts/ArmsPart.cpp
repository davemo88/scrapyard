// Fill out your copyright notice in the Description page of Project Settings.

#include "ArmsPart.h"
#include "SoloDraft.h"

void UArmsPart::Draft(USoloDraft* SoloDraft)
{
	SoloDraft->DraftedArms.AddUnique(this);
}
