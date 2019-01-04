// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "HostEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UHostEntryWidget : public UUserWidget
{
  GENERATED_BODY()

protected:

  virtual void NativeConstruct() override;
	
  UPROPERTY(meta=(BindWidget))
  UEditableTextBox* HostEntryBox;
  UPROPERTY(meta=(BindWidget))
  UButton* JoinButton;
  UPROPERTY(meta=(BindWidget))
  UButton* CancelButton;

  UFUNCTION()
  void Join();
  UFUNCTION()
  void Cancel();

	
};
