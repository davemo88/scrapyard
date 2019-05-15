// Fill out your copyright notice in the Description page of Project Settings.

#include "SoloDraft.h"
#include "PartAssignment.h"

USoloDraft::USoloDraft()
{
  PartAssignment = CreateDefaultSubobject<UPartAssignment>(TEXT("PartAssignment"));  
}
