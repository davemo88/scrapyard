// Fill out your copyright notice in the Description page of Project Settings.


#include "HostEntryWidget.h"

void UHostEntryWidget::NativeConstruct()
{
  JoinButton->OnClicked.AddDynamic(this, &UHostEntryWidget::Join);
  CancelButton->OnClicked.AddDynamic(this, &UHostEntryWidget::Cancel);
//  HostEntryBox->SetText(FText::FromString("127.0.0.1"));
  HostEntryBox->SetHintText(FText::FromString("127.0.0.1"));
}

void UHostEntryWidget::Join()
{
//  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetOwningPlayer()->GetGameInstance());
//  AScrapyardGameSession* GameSession = GameInstance->GetGameSession();
//  GameSession->FindSessions(GetOwningLocalPlayer()->GetPreferredUniqueNetId(), FName(TEXT("DedicatedSession")), true, false);
//  APlayerController* Player = GetOwningPlayer();
//  Player->ClientTravel("3.83.44.150//Game/Levels/BattleLevel", ETravelType::TRAVEL_Absolute);
//  Player->ClientTravel("127.0.0.1//Game/Levels/BattleLevel", ETravelType::TRAVEL_Absolute);
  APlayerController* Player = GetOwningPlayer();
  FString TravelString;
  if (HostEntryBox->GetText().IsEmpty())
  {
    TravelString = "127.0.0.1//Game/Levels/BattleLevel";
  }
  else
  {
    TravelString = FString::Printf(TEXT("%s//Game/Levels/BattleLevel"), *HostEntryBox->GetText().ToString());
  }
  Player->ClientTravel(TravelString, ETravelType::TRAVEL_Absolute);
  UE_LOG(LogTemp, Warning, TEXT("%s::Join - After Client Travel"), *GetName());
}

void UHostEntryWidget::Cancel()
{
  SetVisibility(ESlateVisibility::Hidden);
}



