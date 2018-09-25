// Fill out your copyright notice in the Description page of Project Settings.

#include "LegsPart.h"
#include "Robots/RobotBodyComponent.h"
#include "SoloDraft.h"

void ULegsPart::Draft(USoloDraft* SoloDraft)
{
//  SoloDraft->DraftedLegs.AddUnique(this);
  SoloDraft->DraftedLegs.AddUnique(this->GetClass());
}

void ULegsPart::Assign(URobotBodyComponent* RobotBody)
{
  RobotBody->SetLegs(this);
}
