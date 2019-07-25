// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "InstalledPartWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPartUninstalledDelegate, URobotPart*, UninstalledPart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCompatibleCardDroppedDelegate, UPartCardWidget*, Card);

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UInstalledPartWidget : public UUserWidget
{
  GENERATED_BODY()
  
public:

  UFUNCTION()
  void SetInstalledPart(URobotPart* NewInstalledPart);

  TSubclassOf<URobotPart> InstalledPartType;

  FPartUninstalledDelegate PartUninstalledDelegate;
  FCompatibleCardDroppedDelegate CompatibleCardDroppedDelegate;

protected:

  virtual void NativeConstruct() override;

  bool NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation) override;

  UFUNCTION()
  void OnUninstallButtonClicked();

  UPROPERTY()
  URobotPart* InstalledPart;

  UPROPERTY(meta=(BindWidget))
  UTextBlock* PartName;

  UPROPERTY(meta=(BindWidget))
  UButton* UninstallButton;
  
};
