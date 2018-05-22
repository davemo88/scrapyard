// Fill out your copyright notice in the Description page of Project Settings.

#include "HeadPart.h"
#include "SoloDraft.h"

void UHeadPart::Draft(USoloDraft* SoloDraft)
{
	SoloDraft->DraftedHeads.AddUnique(this);
}
