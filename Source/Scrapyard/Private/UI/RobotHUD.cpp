// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotHUD.h"
#include "Player/RobotPlayerController.h"

ARobotHUD::ARobotHUD()
{
  bShowHUD = 1;
}

void ARobotHUD::DrawHUD()
{
//  UE_LOG(LogTemp, Warning, TEXT("%s::DrawHUD"), *GetName());
  Super::DrawHUD();
//  DrawLine(20,20,40,40,FLinearColor(FColor::Red),10);
//  DrawRect(FLinearColor(FColor::Blue),70,60,50,50); 
  if (ARobotPlayerController* RobotPC = Cast<ARobotPlayerController>(GetOwningPlayerController()))
  {
    if (ARobotCharacter* RoboChar = RobotPC->GetRobotCharacter())
    {
      TArray<FVector> FaceVerts = RoboChar->RobotTargetingComponent->GetBoxFaceVertices();
//      FRotator TargetingRotation = RoboChar->RobotTargetingComponent->RelativeRotation;
      FRotator ViewRotation = RoboChar->GetViewRotation();
      FVector CharLoc = RoboChar->GetActorLocation();

      TArray<FVector2D> TargetingVerts;

      for (FVector Vec : FaceVerts)
      {
        FVector WorldVec = CharLoc + ViewRotation.RotateVector(Vec + FVector(-350/2, 0, 30/2));
        TargetingVerts.Add(FVector2D(Project(WorldVec)));
      }

      uint32 j;
      for (uint32 i = 0; i < TargetingVerts.Num(); ++i)
      {
        j = (i+1) % TargetingVerts.Num();
        DrawLine(
            TargetingVerts[i].X,
            TargetingVerts[i].Y,
            TargetingVerts[j].X,
            TargetingVerts[j].Y,
            FLinearColor(FColor::Red),
            2);
      }
    }
  }
}


