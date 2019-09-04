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

  DrawTargetingSystem();

  if (ARobotPlayerController* RobotPC = Cast<ARobotPlayerController>(GetOwningPlayerController()))
  {
    if (ARobotCharacter* RobotCharacter = RobotPC->GetRobotCharacter())
    {
      switch (RobotCharacter->ControlType) {
        case EControlType::CONTROL_Rectangle:
          DrawControlRectangle();
          break;
        case EControlType::CONTROL_Ellipse:
          DrawControlEllipse();
          break;
      }
    }
  }

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

void ARobotHUD::DrawControlRectangle()
{
  if (ARobotPlayerController* RobotPC = Cast<ARobotPlayerController>(GetOwningPlayerController()))
  {
    if (ARobotCharacter* RobotCharacter = RobotPC->GetRobotCharacter())
    {
      FIntPoint MousePoint;
      GetWorld()->GetGameViewport()->Viewport->GetMousePos(MousePoint);
      FVector2D Mouse = FVector2D(MousePoint);

      const FVector2D ViewSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());

      const FVector2D Center = ViewSize / 2;
      const FVector2D DeadZoneHalfWidth = ViewSize / 10;

      const FVector2D DeadZoneMin = Center - DeadZoneHalfWidth;
      const FVector2D DeadZoneMax = Center + DeadZoneHalfWidth;

      FLinearColor XDeadZoneColor = FLinearColor::Black; 
      FLinearColor YDeadZoneColor = FLinearColor::Black; 

      if (!RobotCharacter->IsInXDeadZone(Mouse))
      {
        XDeadZoneColor = FLinearColor::Green;
        if (Mouse.X < Center.X)
        {
          DrawLine(DeadZoneMin.X, Mouse.Y, Mouse.X, Mouse.Y, FLinearColor::Blue);
          DrawLine(0, Mouse.Y, Mouse.X, Mouse.Y, FLinearColor::Black);
        }
        else
        {
          DrawLine(DeadZoneMax.X, Mouse.Y, Mouse.X, Mouse.Y, FLinearColor::Blue);
          DrawLine(ViewSize.X, Mouse.Y, Mouse.X, Mouse.Y, FLinearColor::Black);
        }
      }

      if (!RobotCharacter->IsInYDeadZone(Mouse))
      {
        XDeadZoneColor = FLinearColor::Green;
        YDeadZoneColor = FLinearColor::Green;

        if (Mouse.Y < Center.Y)
        {
          DrawLine(Mouse.X, DeadZoneMin.Y, Mouse.X, Mouse.Y, FLinearColor::Blue);
          DrawLine(Mouse.X, 0, Mouse.X, Mouse.Y, FLinearColor::Black);
        }
        else
        {
          DrawLine(Mouse.X, DeadZoneMax.Y, Mouse.X, Mouse.Y, FLinearColor::Blue);
          DrawLine(Mouse.X, ViewSize.Y, Mouse.X, Mouse.Y, FLinearColor::Black);
        }
      }

      DrawLine(DeadZoneMin.X, 0, DeadZoneMin.X, ViewSize.Y, XDeadZoneColor, 2); 
      DrawLine(DeadZoneMax.X, 0, DeadZoneMax.X, ViewSize.Y, XDeadZoneColor, 2); 
      DrawLine(0, DeadZoneMin.Y, ViewSize.X, DeadZoneMin.Y, YDeadZoneColor, 2); 
      DrawLine(0, DeadZoneMax.Y, ViewSize.X, DeadZoneMax.Y, YDeadZoneColor, 2); 

//      const FVector2D XDeadZoneIntersection = FVector2D()

//      DrawLine(0, DeadZoneMin.X, ViewSize.Y, DeadZoneMin.X, FLinearColor::Black, 2); 
//      DrawLine(0, DeadZoneMax.X, ViewSize.Y, DeadZoneMax.X, FLinearColor::Black, 2); 

      DrawRect(FLinearColor::Green, Mouse.X, Mouse.Y, 4, 4);
    }
  }
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
// polar coordinates
      float theta1;
      float r1;
      float theta2;
      float r2;
// cartesian
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
// translate to viewport center
        x1 += CenterX;
        y1 += CenterY;
        x2 += CenterX;
        y2 += CenterY;
//        UE_LOG(LogTemp, Warning, TEXT("Centered: x1 - %f y1 - %f x2 - %f y2 - %f "), x1, y1, x2, y2);
//        FLinearColor DrawColor = bIsInDeadZone ? FLinearColor::Red: FLinearColor::Green;
        
//        DrawLine(x1, y1, x2, y2, DrawColor, 2); 
        DrawLine(x1, y1, x2, y2, FLinearColor::Black, 2); 

      }


      float MouseX;
      float MouseY;
      RobotPC->GetMousePosition(MouseX, MouseY);
      FVector2D Mouse = FVector2D(MouseX, MouseY);

//      DrawRect(FLinearColor::Green, MouseX, MouseY, 4, 4);

      bool bIsInDeadZone = RobotCharacter->IsInControlEllipse(Mouse);
      if (!bIsInDeadZone)
      {
        FVector2D Intersection = RobotCharacter->GetControlEllipseIntersection(FVector2D(MouseX, MouseY));
        DrawLine(CenterX, CenterY, Intersection.X, Intersection.Y, FLinearColor::Black, 2); 
        DrawLine(Intersection.X, Intersection.Y, MouseX, MouseY, FLinearColor::Blue, 2); 

        DrawLine(Intersection.X, Intersection.Y, MouseX, Intersection.Y, FLinearColor::Blue, 2); 
        DrawLine(MouseX, Intersection.Y, MouseX < CenterX ? 0 : ViewSize.X, Intersection.Y, FLinearColor::Black, 2); 

        DrawLine(Intersection.X, Intersection.Y, Intersection.X, MouseY, FLinearColor::Blue, 2); 
        DrawLine(Intersection.X, MouseY, Intersection.X, MouseY < CenterY ? 0 : ViewSize.Y, FLinearColor::Black, 2); 

// treat center of viewport as origin
        float CenteredMouseX = MouseX - CenterX;
// top left is 0,0 in viewport space
        float CenteredMouseY = CenterY - MouseY;

        float m = CenteredMouseY / CenteredMouseX;

        float EdgeIntersectionX = CenteredMouseX > 0 
          ? FMath::Min(CenterX, FMath::Abs((CenterY / m))) + CenterX
          : FMath::Max(-CenterX, -FMath::Abs((CenterY / m))) + CenterX;
        float EdgeIntersectionY = CenteredMouseY > 0 
          ? CenterY - FMath::Min(CenterY, FMath::Abs(CenterX * m)) 
          : CenterY - FMath::Max(-CenterY, -FMath::Abs(CenterX * m));
//        UE_LOG(LogTemp, Warning, TEXT("CenterY / m = %f"), CenterY / m);
//        UE_LOG(LogTemp, Warning, TEXT("CenterX * m = %f"), CenterX * m);
//        UE_LOG(LogTemp, Warning, TEXT("MouseX: %f MouseY: %f"), MouseX, MouseY);
//        UE_LOG(LogTemp, Warning, TEXT("CenterX: %f CenterY: %f"), CenterX, CenterY);
//        UE_LOG(LogTemp, Warning, TEXT("CenteredMouseX: %f CenteredMouseY: %f m: %f"), CenteredMouseX, CenteredMouseY, m);
//        UE_LOG(LogTemp, Warning, TEXT("EdgeIntersectionX: %f EdgeIntersectionY: %f"), EdgeIntersectionX, EdgeIntersectionY);
        DrawLine(MouseX, MouseY, EdgeIntersectionX, EdgeIntersectionY, FLinearColor::Black, 2); 
        DrawRect(FLinearColor::Green, Intersection.X, Intersection.Y, 4, 4);
        DrawRect(FLinearColor::Green, MouseX, MouseY, 4, 4);

      }
      else
      {
        DrawLine(CenterX, CenterY, MouseX, MouseY, FLinearColor::Black, 2); 
      }
    }
  }
}

float ARobotHUD::GetControlEllipseRadius(float theta, float a, float b)
{
  return (a * b) / FMath::Sqrt(FMath::Square(b * FMath::Cos(theta)) + FMath::Square(a * FMath::Sin(theta)));
}
