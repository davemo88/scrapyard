// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotStatsWidget.h"
#include "StatLineWidget.h"


void URobotStatsWidget::SetRobotStats(URobotStats* NewRobotStats)
{
  RobotStats = NewRobotStats;
  RobotStats->RobotStatsUpdatedDelegate.AddDynamic(this, &URobotStatsWidget::UpdateStats);
}

void URobotStatsWidget::UpdateStats()
{
  MassStatLine->SetStatValue(FText::AsNumber(RobotStats->Mass));
}

