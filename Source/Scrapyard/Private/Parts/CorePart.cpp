// Fill out your copyright notice in the Description page of Project Settings.

#include "CorePart.h"
#include "Robots/RobotBodyComponent.h"
#include "SoloDraft.h"

void UCorePart::Draft(USoloDraft* SoloDraft)
{
	SoloDraft->DraftedCores.AddUnique(this);
}

void UCorePart::Assign(URobotBodyComponent* RobotBody)
{
	RobotBody->SetCore(this);
}
