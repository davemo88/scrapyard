// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotHUD.h"
#include "Engine/Canvas.h"
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
    if (ARobotCharacter* RobotCharacter = RobotPC->GetRobotCharacter())
    {
      FVector CameraOffset = RobotCharacter->CameraBoom->SocketOffset + FVector(-RobotCharacter->CameraBoom->TargetArmLength,0,0);

      TArray<FVector> FaceVerts = RobotCharacter->RobotTargetingComponent->GetFaceVerts();

      FRotator ViewRotation = RobotCharacter->GetViewRotation();
      FVector TargetingOrigin = RobotCharacter->GetActorLocation() + ViewRotation.RotateVector(CameraOffset);
      TArray<FVector2D> HUDVerts;
      for (FVector Vec : FaceVerts)
      {
        FVector WorldVec = TargetingOrigin + ViewRotation.RotateVector(Vec);
        HUDVerts.Add(FVector2D(Project(WorldVec)));
      }

      uint NumVerts = HUDVerts.Num();
      uint j;
      for (uint i = 0; i < NumVerts ; i++)
      {
        j = (i+1) % NumVerts; 
        DrawLine(
            HUDVerts[i].X,
            HUDVerts[i].Y,
            HUDVerts[j].X,
            HUDVerts[j].Y,
            GetTargetingColor(),
            2);
      }

//      FVector RelativeCenter = FVector(RobotCharacter->RobotTargetingComponent->GetRange(),0,0);
//      FVector WorldCenter = RobotCharacter->GetActorLocation() + RobotCharacter->GetViewRotation().RotateVector(RelativeCenter);
//      UE_LOG(LogTemp, Warning, TEXT("%s::DrawHUD RelativeCenter - %s"), *GetName(), *RelativeCenter.ToString());
//      UE_LOG(LogTemp, Warning, TEXT("%s::DrawHUD WorldCenter - %s"), *GetName(), *WorldCenter.ToString());
//
//      FVector RelativeEdge = FVector(RobotCharacter->RobotTargetingComponent->GetRange(),0,0);
//      FVector WorldEdge = RobotCharacter->GetActorLocation() + RobotCharacter->GetViewRotation().RotateVector(RelativeCenter);
//      UE_LOG(LogTemp, Warning, TEXT("%s::DrawHUD RelativeCenter - %s"), *GetName(), *RelativeCenter.ToString());
//      UE_LOG(LogTemp, Warning, TEXT("%s::DrawHUD WorldCenter - %s"), *GetName(), *WorldCenter.ToString());

//      FVector2D CenterScreenLoc = Project(WorldCenter);


//      TArray<FVector> FaceVerts = RoboChar->RobotTargetingComponent->GetBoxFaceVertices();
////      FRotator TargetingRotation = RoboChar->RobotTargetingComponent->RelativeRotation;
//      FRotator ViewRotation = RoboChar->GetViewRotation();
//      FVector CharLoc = RoboChar->GetActorLocation();
//
//      TArray<FVector2D> TargetingVerts;
//
//      for (FVector Vec : FaceVerts)
//      {
//        FVector WorldVec = CharLoc + ViewRotation.RotateVector(Vec);
//        TargetingVerts.Add(FVector2D(Project(WorldVec)));
//      }
//
//      uint32 j;
////      for (uint32 i = 0; i < TargetingVerts.Num(); ++i)
////      far face verts
//      for (uint32 i = 0; i < 4; i+=2)
//      {
//        j = (i+1) % 4;
//        DrawLine(
//            TargetingVerts[i].X,
//            TargetingVerts[i].Y,
//            TargetingVerts[j].X,
//            TargetingVerts[j].Y,
//            GetTargetingColor(),
//            2);
//      }
//// close face verts
//      for (uint32 i = 4; i < 8; ++i)
//      {
//        j = (i) % 4;
//        DrawLine(
//            TargetingVerts[i].X,
//            TargetingVerts[i].Y,
//            TargetingVerts[j].X,
//            TargetingVerts[j].Y,
//            GetTargetingColor(),
//            2);
//      }
    }
  }
}

FLinearColor ARobotHUD::GetTargetingColor()
{
  if (ARobotPlayerController* RobotPC = Cast<ARobotPlayerController>(GetOwningPlayerController()))
  {
    if (ARobotCharacter* RoboChar = RobotPC->GetRobotCharacter())
    {
      if (RoboChar->bTargetAcquired)
      {
        return FLinearColor(FColor::Green);
      }
    }
  }

  return FLinearColor(FColor::Red);
    
}

