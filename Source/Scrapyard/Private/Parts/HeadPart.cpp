// Fill out your copyright notice in the Description page of Project Settings.

#include "HeadPart.h"
#include "Robots/RobotBodyComponent.h"
#include "SoloDraft.h"

void UHeadPart::Draft(USoloDraft* SoloDraft)
{
//  SoloDraft->DraftedHeads.AddUnique(this);
  SoloDraft->DraftedHeads.AddUnique(this->GetClass());
}

void UHeadPart::Assign(URobotBodyComponent* RobotBody)
{
//  RobotBody->SetHead(this);
}
