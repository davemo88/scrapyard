// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniYourPartsWidget.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "UI/UIAssets.h"
#include "UI/CardWidgetBase.h"
#include "UI/MiniCardWidget.h"

UCardWidgetBase* UMiniYourPartsWidget::GetCardWidget()
{
  return CreateWidget<UMiniCardWidget>(GetOwningPlayer(), UScrapyardGameInstance::GameInstance->AssetsBP->UIAssetsBP->MiniCardWidgetBP); 
}
