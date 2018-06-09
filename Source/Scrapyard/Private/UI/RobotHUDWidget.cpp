// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotHUDWidget.h"
#include "Robots/RobotCharacter.h"

void URobotHUDWidget::SetRobotCharacter(ARobotCharacter* _RobotCharacter)
{
	RobotCharacter = _RobotCharacter;
}

float URobotHUDWidget::GetPowerPercent()
{
	return (float)RobotCharacter->Power / (float)RobotCharacter->RobotStats->MaxPower;
}

