// Fill out your copyright notice in the Description page of Project Settings.

#include "SoloDraft.h"
#include "RobotPartAssignment.h"

USoloDraft::USoloDraft()
{
  PartAssignment = CreateDefaultSubobject<URobotPartAssignment>(TEXT("PartAssignment"));  
}
