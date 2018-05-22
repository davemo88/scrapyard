// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPartAssignment.h"

bool URobotPartAssignment::IsComplete()
{
	return (Head != nullptr && Core != nullptr && Arms != nullptr && Legs != nullptr);
}