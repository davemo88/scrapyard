// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchStatusWidget.h"
#include "Game/RobotGameState.h" 

void UMatchStatusWidget::NativeConstruct()
{
  MatchTime->SetVisibility(ESlateVisibility::Hidden); 
}

void UMatchStatusWidget::SetAnnouncement(FText AnnouncementText)
{
  Announcement->SetText(AnnouncementText);
}
 
void UMatchStatusWidget::StartMatchTimer() 
{ 
  UE_LOG(LogTemp, Warning, TEXT("%s::StartMatchTimer"), *GetName()); 
  MatchTime->SetVisibility(ESlateVisibility::Visible); 
  UpdateMatchTimer(); 
} 
 
void UMatchStatusWidget::StopMatchTimer() 
{ 
  UE_LOG(LogTemp, Warning, TEXT("%s::StopMatchTimer"), *GetName()); 
  MatchTime->SetVisibility(ESlateVisibility::Hidden); 
} 
 
void UMatchStatusWidget::UpdateMatchTimer() 
{ 
  UE_LOG(LogTemp, Warning, TEXT("%s::UpdateMatchTimer"), *GetName()); 
  if (ARobotGameState* RobotGS = Cast<ARobotGameState>(GetWorld()->GetGameState())) 
  { 
    MatchTime->SetText(FText::AsNumber(RobotGS->GetMatchTimerSecondsRemaining())); 
  } 
} 




