// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPartComponent.h"

void URobotPartComponent::AssignPart(URobotPart* Part)
{
	AssignedPart = Part;
	SetSkeletalMesh(Part->SkeletalMesh);
	SetMaterial(0, Part->MajorMaterial);
}