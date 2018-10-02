// Fill out your copyright notice in the Description page of Project Settings.

#include "PartCardWidget.h"
#include "Parts/RobotPart.h"

void UPartCardWidget::SetRobotPart(URobotPart* NewRobotPart)
{
	RobotPart = NewRobotPart;
}

void UPartCardWidget::SetRobotPart(URobotPart* NewRobotPart)
{
	RobotPart = NewRobotPart;
}

void UPartCardWidget::OnPartCardClicked()
{
	PartCardClickedDelegate.Broadcast(RobotPart);
}
