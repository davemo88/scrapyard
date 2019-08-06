// Fill out your copyright notice in the Description page of Project Settings.


#include "FancyYourPartsWidget.h"
#include "Scrapyard.h"
#include "Parts/RobotPart.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/BoosterPart.h"
#include "Parts/HandheldPart.h"
#include "Parts/ChipPart.h"

void UFancyYourPartsWidget::NativeConstruct()
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeConstruct"), *GetName());
  Super::NativeConstruct();

//  AllFilterButton->OnClicked.AddDynamic(this, &UFancyYourPartsWidget::OnAllFilterButtonClicked);
//  HeadFilterButton->OnClicked.AddDynamic(this, &UFancyYourPartsWidget::OnHeadFilterButtonClicked);
//  CoreFilterButton->OnClicked.AddDynamic(this, &UFancyYourPartsWidget::OnCoreFilterButtonClicked);
//  ArmsFilterButton->OnClicked.AddDynamic(this, &UFancyYourPartsWidget::OnArmsFilterButtonClicked);
//  LegsFilterButton->OnClicked.AddDynamic(this, &UFancyYourPartsWidget::OnLegsFilterButtonClicked);
//  BoosterFilterButton->OnClicked.AddDynamic(this, &UFancyYourPartsWidget::OnBoosterFilterButtonClicked);
//  HandheldFilterButton->OnClicked.AddDynamic(this, &UFancyYourPartsWidget::OnHandheldFilterButtonClicked);
//  DefaultPartsFilterButton->OnClicked.AddDynamic(this, &UFancyYourPartsWidget::OnDefaultPartsFilterButtonClicked);

  bDisplayDefaultParts = false;

} 

void UFancyYourPartsWidget::OnAllFilterButtonClicked()
{
  UE_LOG(LogUI, Log, TEXT("%s::OnAllFilterButtonClicked"), *GetName());

  bDisplayDefaultParts = false;
  DisplayAll();
}

void UFancyYourPartsWidget::OnHeadFilterButtonClicked()
{
  UE_LOG(LogUI, Log, TEXT("%s::OnHeadFilterButtonClicked"), *GetName());

  bDisplayDefaultParts = false;
  DisplayParts(CurrentDraft->DraftedParts.FilterByPredicate([](URobotPart* Part){return Part->IsA(UHeadPart::StaticClass());}));
}

void UFancyYourPartsWidget::OnCoreFilterButtonClicked()
{
  UE_LOG(LogUI, Log, TEXT("%s::OnCoreFilterButtonClicked"), *GetName());

  bDisplayDefaultParts = false;
  DisplayParts(CurrentDraft->DraftedParts.FilterByPredicate([](URobotPart* Part){return Part->IsA(UCorePart::StaticClass());}));
}

void UFancyYourPartsWidget::OnArmsFilterButtonClicked()
{
  UE_LOG(LogUI, Log, TEXT("%s::OnArmsFilterButtonClicked"), *GetName());

  bDisplayDefaultParts = false;
  DisplayParts(CurrentDraft->DraftedParts.FilterByPredicate([](URobotPart* Part){return Part->IsA(UArmsPart::StaticClass());}));
}

void UFancyYourPartsWidget::OnLegsFilterButtonClicked()
{
  UE_LOG(LogUI, Log, TEXT("%s::OnLegsFilterButtonClicked"), *GetName());

  bDisplayDefaultParts = false;
  DisplayParts(CurrentDraft->DraftedParts.FilterByPredicate([](URobotPart* Part){return Part->IsA(ULegsPart::StaticClass());}));
}

void UFancyYourPartsWidget::OnBoosterFilterButtonClicked()
{
  UE_LOG(LogUI, Log, TEXT("%s::OnBoosterFilterButtonClicked"), *GetName());

  bDisplayDefaultParts = false;
  DisplayParts(CurrentDraft->DraftedParts.FilterByPredicate([](URobotPart* Part){return Part->IsA(UBoosterPart::StaticClass());}));
}

void UFancyYourPartsWidget::OnHandheldFilterButtonClicked()
{
  UE_LOG(LogUI, Log, TEXT("%s::OnHandheldFilterButtonClicked"), *GetName());

  bDisplayDefaultParts = false;
  DisplayParts(CurrentDraft->DraftedParts.FilterByPredicate([](URobotPart* Part){return Part->IsA(UHandheldPart::StaticClass());}));
}

void UFancyYourPartsWidget::OnChipFilterButtonClicked()
{
  UE_LOG(LogUI, Log, TEXT("%s::OnChipFilterButtonClicked"), *GetName());

  bDisplayDefaultParts = false;
  DisplayParts(CurrentDraft->DraftedParts.FilterByPredicate([](URobotPart* Part){return Part->IsA(UChipPart::StaticClass());}));
}

void UFancyYourPartsWidget::OnDefaultPartsFilterButtonClicked()
{
  UE_LOG(LogUI, Log, TEXT("%s::OnDefaultPartsFilterButtonClicked"), *GetName());

  bDisplayDefaultParts = true;
  DisplayParts(CurrentDraft->GetDefaultParts());
}


