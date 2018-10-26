// Fill out your copyright notice in the Description page of Project Settings.

#include "CorePart.h"
#include "RobotPartAssignment.h"
#include "SoloDraft.h"

void UCorePart::Draft(USoloDraft* SoloDraft)
{
//	SoloDraft->DraftedCores.AddUnique(this);
	SoloDraft->DraftedCores.AddUnique(this);
}

void UCorePart::Assign(URobotPartAssignment* PartAssignment)
{
  PartAssignment->SetCore(this);
}

TSoftObjectPtr<UTexture2D> UCorePart::GetCardIconAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->CoreCardIcon: nullptr;
}
