// Fill out your copyright notice in the Description page of Project Settings.

#include "ArmsPart.h"
#include "Robots/RobotBodyComponent.h"
#include "SoloDraft.h"

void UArmsPart::Draft(USoloDraft* SoloDraft)
{
//  SoloDraft->DraftedArms.AddUnique(this);
  UE_LOG(LogTemp, Warning, TEXT("Drafted %s"), *this->GetClass()->GetName());
  SoloDraft->DraftedArms.AddUnique(this->GetClass());
}

void UArmsPart::Assign(URobotBodyComponent* RobotBody)
{
//  RobotBody->SetArms(this);
}
