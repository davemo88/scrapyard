// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Player/RobotPlayerController.h"

ARobotHUD::ARobotHUD()
{
  bShowHUD = 1;
}

void ARobotHUD::DrawHUD()
{
  Super::DrawHUD();
//  DrawTargetingSystem();
  DrawControlEllipse();
//  DrawLine(20,20,40,40,FLinearColor(FColor::Red),10);
//  DrawRect(FLinearColor(FColor::Blue),70,60,50,50); 
//      FVector RelativeCenter = FVector(RobotCharacter->RobotTargetingComponent->GetRange(),0,0);
//      FVector WorldCenter = RobotCharacter->GetActorLocation() + RobotCharacter->GetViewRotation().RotateVector(RelativeCenter);
//
//      FVector RelativeEdge = FVector(RobotCharacter->RobotTargetingComponent->GetRange(),0,0);
//      FVector WorldEdge = RobotCharacter->GetActorLocation() + RobotCharacter->GetViewRotation().RotateVector(RelativeCenter);

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

void ARobotHUD::DrawTargetingSystem()
{
  if (ARobotPlayerController* RobotPC = Cast<ARobotPlayerController>(GetOwningPlayerController()))
  {
    if (ARobotCharacter* RobotCharacter = RobotPC->GetRobotCharacter())
    {
      FVector CameraLocation = RobotPC->PlayerCameraManager->GetCameraLocation();
      FRotator ViewRotation = RobotCharacter->GetViewRotation();

      TArray<FVector> FaceVerts = RobotCharacter->RobotTargetingComponent->GetFaceVerts();

      TArray<FVector2D> HUDVerts;
      for (FVector Vec : FaceVerts)
      {
        FVector WorldVec =  CameraLocation + ViewRotation.RotateVector(Vec);
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

      TArray<AActor*> Targets = RobotCharacter->RobotTargetingComponent->GetTargets();
//
//      for (AActor* Target : Targets)
//
      for (int i = 0; i < Targets.Num(); ++i)
      {
        FVector2D ScreenLocation = FVector2D(Project(Targets[i]->GetActorLocation()));
        if (i == 0)
        {
          DrawRect(FLinearColor::Green, ScreenLocation.X, ScreenLocation.Y, 4.0f, 4.0f);
        }
        else
        {
          DrawRect(FLinearColor::Blue, ScreenLocation.X, ScreenLocation.Y, 4.0f, 4.0f);
        }
      }
    }
  }
}

FLinearColor ARobotHUD::GetTargetingColor()
{
  if (ARobotPlayerController* RobotPC = Cast<ARobotPlayerController>(GetOwningPlayerController()))
  {
    if (ARobotCharacter* RoboChar = RobotPC->GetRobotCharacter())
    {
      if (RoboChar->IsTargetAcquired())
      {
        return FLinearColor(FColor::Green);
      }
    }
  }

  return FLinearColor(FColor::Red);
    
}

void ARobotHUD::DrawTargetBox(AActor* Target)
{

}

void ARobotHUD::DrawControlEllipse()
{
  const FVector2D ViewSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());


  float CenterX = ViewSize.X / 2.0f;
  float CenterY = ViewSize.Y / 2.0f;
// control ellipse horizontal axis
  float a = ViewSize.X / 10.0f;
// control ellipse vertical axis
  float b = ViewSize.Y / 10.0f;

//  UE_LOG(LogTemp, Warning, TEXT("ViewportSize: %s"), *ViewSize.ToString());
//  UE_LOG(LogTemp, Warning, TEXT("a - %f b - %f "), a, b);

  if (ARobotPlayerController* RobotPC = Cast<ARobotPlayerController>(GetOwningPlayerController()))
  {
    if (ARobotCharacter* RobotCharacter = RobotPC->GetRobotCharacter())
    {
      float theta1;
      float r1;
      float theta2;
      float r2;
      float x1;
      float y1;
      float x2;
      float y2;
      uint32 j;
      uint32 NumPoints = 40;
//      UE_LOG(LogTemp, Warning, TEXT("begin control ellipse draw loop"));
//      UE_LOG(LogTemp, Warning, TEXT("PI - %f"), PI);
      for (uint32 i = 0; i < NumPoints; ++i)
      {
        theta1 = i * ((2 * PI) / NumPoints);
        r1 = GetControlEllipseRadius(theta1, a, b);
        j = (i + 1) % NumPoints; 
        theta2 = j * ((2 * PI) / NumPoints);
        r2 = GetControlEllipseRadius(theta2, a, b);
        FMath::PolarToCartesian(r1, theta1, x1, y1);
        FMath::PolarToCartesian(r2, theta2, x2, y2);
//        UE_LOG(LogTemp, Warning, TEXT("a - %f b - %f "), a, b);
//        UE_LOG(LogTemp, Warning, TEXT("x1 - %f y1 - %f x2 - %f y2 - %f "), x1, y1, x2, y2);
//        UE_LOG(LogTemp, Warning, TEXT("theta1 - %f theta2 - %f r1 - %f r2 - %f "), theta1, theta2, r1, r2);
        x1 += CenterX;
        y1 += CenterY;
        x2 += CenterX;
        y2 += CenterY;
//        UE_LOG(LogTemp, Warning, TEXT("Centered: x1 - %f y1 - %f x2 - %f y2 - %f "), x1, y1, x2, y2);
        DrawLine( x1, y1, x2, y2, FLinearColor::Red, 2); 
      }
    }
  }

}

float ARobotHUD::GetControlEllipseRadius(float theta, float a, float b)
{
  return (a * b) / FMath::Sqrt(FMath::Square(b * FMath::Cos(theta)) + FMath::Square(a * FMath::Sin(theta)));
}
