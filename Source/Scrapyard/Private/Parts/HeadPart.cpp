// Fill out your copyright notice in the Description page of Project Settings.

#include "HeadPart.h"
#include "SoloDraft.h"
#include "Robots/RobotPartAssignment.h"

void UHeadPart::Draft(USoloDraft* SoloDraft)
{
	SoloDraft->DraftedHeads.AddUnique(this);
}

void UHeadPart::Assign(URobotPartAssignment* PartAssignment)
{
	PartAssignment->Head = this;
}