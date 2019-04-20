// Fill out your copyright notice in the Description page of Project Settings.
//

#include "EscapeMenuWidget.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardDefaultAssets.h"
#include "UI/RobotTunerWidget.h"
#include "Kismet/GameplayStatics.h"

void UEscapeMenuWidget::NativeConstruct()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::NativeConstruct"), *GetName());
  Super::NativeConstruct();

  OptionsButton->OnClicked.AddDynamic(this, &UEscapeMenuWidget::Options);
  QuitToMainMenuButton->OnClicked.AddDynamic(this, &UEscapeMenuWidget::QuitToMainMenu);
  QuitToDesktopButton->OnClicked.AddDynamic(this, &UEscapeMenuWidget::QuitToDesktop);
  TunerWidgetButton->OnClicked.AddDynamic(this, &UEscapeMenuWidget::ShowTunerWidget);

  TunerWidget->SetVisibility(ESlateVisibility::Hidden);

}

void UEscapeMenuWidget::NativeOnInitialized()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::NativeOnInitialized"), *GetName());
  Super::NativeOnInitialized();
  
}

void UEscapeMenuWidget::Options()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::Options"), *GetName());
}
	
void UEscapeMenuWidget::QuitToMainMenu()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::QuitToMainMenu"), *GetName());
  UWorld* World = GetWorld();
  UGameplayStatics::OpenLevel(World, "/Game/Levels/MainLevel");
  
}

void UEscapeMenuWidget::QuitToDesktop()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::QuitToDesktop"), *GetName());
  FGenericPlatformMisc::RequestExit(false);
}

void UEscapeMenuWidget::ShowTunerWidget()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::ShowTunerWidget"), *GetName());
  ARobotCharacter* RobotChar = Cast<ARobotCharacter>(GetOwningPlayer()->GetPawn());
  if (TunerWidget->RobotChar != nullptr && TunerWidget->RobotChar->IsLocallyControlled())
  {
    TunerWidget->SetVisibility(ESlateVisibility::Visible);
  }
}
