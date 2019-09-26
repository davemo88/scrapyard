

#include "RobotTunerWidget.h"
#include "Scrapyard.h"
#include "Player/RobotPlayerController.h"



void URobotTunerWidget::NativeConstruct()
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeConstruct"), *GetName());
  Super::NativeConstruct();
  
  SetNewTuneButton->OnClicked.AddDynamic(this, &URobotTunerWidget::SetNewTune);

// https://wiki.unrealengine.com/Enums_For_Both_C%2B%2B_and_BP
  const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EControlType"), true);
  ControlTypeComboBox->AddOption(EnumPtr->GetNameStringByValue((int64)EControlType::CONTROL_Normal));
  ControlTypeComboBox->AddOption(EnumPtr->GetNameStringByValue((int64)EControlType::CONTROL_Rectangle));
  ControlTypeComboBox->AddOption(EnumPtr->GetNameStringByValue((int64)EControlType::CONTROL_Ellipse));
  ControlTypeComboBox->RefreshOptions();

  if (APlayerController* PC = GetOwningPlayer())
  {
    SetRobotChar(Cast<ARobotCharacter>(PC->GetPawn()));
  }

}

void URobotTunerWidget::SetRobotChar(ARobotCharacter* NewRobotChar)
{
  UE_LOG(LogUI, Log, TEXT("%s::SetRobotChar"), *GetName());
  if (NewRobotChar)
  {
    RobotChar = NewRobotChar;
    RobotMovementComp = Cast<URobotMovementComponent>(RobotChar->GetMovementComponent());

    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EControlType"), true);
    ControlTypeComboBox->SetSelectedOption(EnumPtr->GetNameStringByValue((int64)RobotChar->ControlType));
    DeadZoneSizeTextBox->SetText(FText::AsNumber(RobotChar->DeadZoneFactor));
    MaxPitchRateTextBox->SetText(FText::AsNumber(RobotChar->MaxPitchRate));
  }

  if (RobotMovementComp)
  {
    GroundFrictionTextBox->SetText(FText::AsNumber(RobotMovementComp->GroundFriction));
    BoostHoldThresholdTimeTextBox->SetText(FText::AsNumber(RobotMovementComp->BoostHoldThresholdTime));
  }


}

void URobotTunerWidget::SetNewTune()
{
  UE_LOG(LogUI, Log, TEXT("%s::SetNewTune"), *GetName());
  FRobotTuneParams TuneParams = GetTuneParams();
  if (ARobotPlayerController* RobotPC = Cast<ARobotPlayerController>(GetOwningPlayer()))
  {
    RobotPC->SetNewTune(TuneParams);
  }

  SetVisibility(ESlateVisibility::Hidden);
}

FRobotTuneParams URobotTunerWidget::GetTuneParams()
{
  FRobotTuneParams TuneParams;

  TuneParams.GroundFriction = GroundFrictionTextBox->GetText().ToString();
  TuneParams.BoostHoldThresholdTime = BoostHoldThresholdTimeTextBox->GetText().ToString();
  TuneParams.ControlType = ControlTypeComboBox->GetSelectedOption();
  TuneParams.DeadZoneSize = DeadZoneSizeTextBox->GetText().ToString();
  TuneParams.MaxPitchRate = MaxPitchRateTextBox->GetText().ToString();
//  TuneParams.ControlType = 
  UE_LOG(LogUI, Log, TEXT("GetTuneParams BoostHoldThresholdTime: %s"), *TuneParams.BoostHoldThresholdTime);

  return TuneParams;
}
