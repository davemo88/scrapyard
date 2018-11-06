// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotPartAssignment.h"


void URobotPartAssignment::SetHead(UHeadPart* NewHead)
{
  Head = NewHead;
  PartAssignmentChangedDelegate.Broadcast();
  HeadAssignmentChangedDelegate.Broadcast(NewHead);
}

void URobotPartAssignment::SetCore(UCorePart* NewCore)
{
  Core = NewCore;
  PartAssignmentChangedDelegate.Broadcast();
  CoreAssignmentChangedDelegate.Broadcast(NewCore);
}

void URobotPartAssignment::SetArms(UArmsPart* NewArms)
{
  Arms = NewArms;
  PartAssignmentChangedDelegate.Broadcast();
  ArmsAssignmentChangedDelegate.Broadcast(NewArms);
}

void URobotPartAssignment::SetLegs(ULegsPart* NewLegs)
{
  Legs = NewLegs;
  PartAssignmentChangedDelegate.Broadcast();
  LegsAssignmentChangedDelegate.Broadcast(NewLegs);
}

void URobotPartAssignment::CopyAssignment(URobotPartAssignment* NewPartAssignment)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::CopyAssignment"), *GetName());
  Head = NewPartAssignment->Head;
  Core = NewPartAssignment->Core;
  Arms = NewPartAssignment->Arms;
  Legs = NewPartAssignment->Legs;
  HeadAssignmentChangedDelegate.Broadcast(Head);
  CoreAssignmentChangedDelegate.Broadcast(Core);
  ArmsAssignmentChangedDelegate.Broadcast(Arms);
  LegsAssignmentChangedDelegate.Broadcast(Legs);
  PartAssignmentChangedDelegate.Broadcast();
}

UHeadPart* URobotPartAssignment::GetHead()
{
  return Head;
}

UCorePart* URobotPartAssignment::GetCore()
{
  return Core;
}

UArmsPart* URobotPartAssignment::GetArms()
{
  return Arms;
}

ULegsPart* URobotPartAssignment::GetLegs()
{
  return Legs;
}

