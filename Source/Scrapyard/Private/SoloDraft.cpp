// Fill out your copyright notice in the Description page of Project Settings.

#include "SoloDraft.h"

USoloDraft::USoloDraft()
{
	CurrentPack = CreateDefaultSubobject<URobotPartAssignment>(TEXT("CurrentDraft"));
}