// Fill out your copyright notice in the Description page of Project Settings.
//

#include "EscapeMenuWidget.h"
#include "Kismet/GameplayStatics.h"

void UEscapeMenuWidget::NativeConstruct()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::NativeConstruct"), *GetName());
  Super::NativeConstruct();

  OptionsButton->OnClicked.AddDynamic(this, &UEscapeMenuWidget::Options);
  QuitToMainMenuButton->OnClicked.AddDynamic(this, &UEscapeMenuWidget::QuitToMainMenu);
  QuitToDesktopButton->OnClicked.AddDynamic(this, &UEscapeMenuWidget::QuitToDesktop);
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

