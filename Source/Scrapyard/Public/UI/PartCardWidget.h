// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "PartCardWidget.generated.h"

class URobotPart;
struct FStatText;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardClickedDelegate, URobotPart*, Part);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardDoubleClickedDelegate, URobotPart*, Part);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardMouseEnteredDelegate, URobotPart*, Part);

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UPartCardWidget : public UUserWidget
{
  GENERATED_BODY()

public:

  void SetRobotPart(URobotPart* RobotPart);
  void SetRobotPart(TSubclassOf<URobotPart> RobotPartClass);

  UPROPERTY(BlueprintReadOnly)
  URobotPart* RobotPart;

  UPROPERTY(BlueprintReadOnly)
  TSubclassOf<URobotPart> RobotPartClass;

  FCardClickedDelegate CardClickedDelegate;
  FCardDoubleClickedDelegate CardDoubleClickedDelegate;

  FCardMouseEnteredDelegate CardMouseEnteredDelegate;

protected:

  void NativeOnMouseEnter(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent) override;

  void NativeOnMouseLeave(const FPointerEvent & InMouseEvent) override;

  FReply NativeOnMouseButtonDoubleClick(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent) override;

  void AddStatsText();

  void AddStatLine(FStatText StatText);

  UFUNCTION()
  void OnPartCardClicked();

  UPROPERTY(meta=(BindWidget))
  UBorder* CardBackground;

  UPROPERTY(meta=(BindWidget))
  UImage* PartTypeIcon;

  UPROPERTY(meta=(BindWidget))
  UVerticalBox* StatsBox;

};
