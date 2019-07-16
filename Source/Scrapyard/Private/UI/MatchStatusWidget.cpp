// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchStatusWidget.h"
#include "Scrapyard.h"
#include "Game/RobotGameState.h" 

void UMatchStatusWidget::NativeConstruct()
{
  MatchTime->SetVisibility(ESlateVisibility::Hidden); 
  ScreenBlocker->SetVisibility(ESlateVisibility::Hidden);
}

void UMatchStatusWidget::SetAnnouncement(FText AnnouncementText)
{
  Announcement->SetText(AnnouncementText);
}
 
void UMatchStatusWidget::StartMatchTimer() 
{ 
  UE_LOG(LogUI, Log, TEXT("%s::StartMatchTimer"), *GetName()); 
  MatchTime->SetVisibility(ESlateVisibility::Visible); 
  UpdateMatchTimer(); 
} 
 
void UMatchStatusWidget::StopMatchTimer() 
{ 
  UE_LOG(LogUI, Log, TEXT("%s::StopMatchTimer"), *GetName()); 
  MatchTime->SetVisibility(ESlateVisibility::Hidden); 
} 
 
void UMatchStatusWidget::UpdateMatchTimer() 
{ 
  UE_LOG(LogUI, Log, TEXT("%s::UpdateMatchTimer"), *GetName()); 
  if (ARobotGameState* RobotGS = Cast<ARobotGameState>(GetWorld()->GetGameState())) 
  { 
    MatchTime->SetText(FText::AsNumber(RobotGS->GetMatchTimerSecondsRemaining())); 
  } 
} 

void UMatchStatusWidget::OnReadyToStartMatch(bool bReady)
{
  if (ARobotGameState* RobotGS = Cast<ARobotGameState>(GetWorld()->GetGameState())) 
  { 
    if (RobotGS->GetMatchState() == FName("WaitingToStart"))
    {
      if (bReady)
      {
        SetAnnouncement(NSLOCTEXT("SY","WaitingToStart","Battle Starting"));
      }
      else
      {
        SetAnnouncement(NSLOCTEXT("SY","WaitingToStart","Waiting To Start Battle"));
      }
    }
    else
    {
// this shouldn't happen
      UE_LOG(LogUI, Log, TEXT("%s::OnReadyToStartMatch - called outside of WaitingToStart state"), *GetName());
    }
  } 

}

void UMatchStatusWidget::ShowScreenBlocker()
{
  UE_LOG(LogUI, Log, TEXT("%s::ShowScreenBlocker"), *GetName()); 
  ScreenBlocker->SetVisibility(ESlateVisibility::HitTestInvisible);
  PlayAnimation(ScreenBlockerFade);
}

