// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPlayerState.h"

int32 ARobotPlayerState::GetTeam()
{
  return Team;
}

void ARobotPlayerState::SetTeam(int32 NewTeam)
{
  Team = NewTeam;
}



