// Fill out your copyright notice in the Description page of Project Settings.

#include "SoloDraft.h"
#include "Robots/RobotPartAssignment.h"

USoloDraft::USoloDraft()
{
	CurrentPack = CreateDefaultSubobject<URobotPartAssignment>(TEXT("CurrentDraft"));
}
