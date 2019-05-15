// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Parts/RobotPart.h"
#include "Parts/Manufacturer.h"
#include "PartSingleton.generated.h"

USTRUCT()
struct FPartDatabase
{
  GENERATED_BODY()

  void AddPart(URobotPart* NewPart)
  {
    PartMap.Add(NewPart->PartID, NewPart);
  };

  template <class T>
  T* GetPart(uint32 PartID)
  {
    if (PartMap.Find(PartID))
    {
      return Cast<T>(PartMap[PartID]);
    };
    return nullptr;
  };

  URobotPart* GetPart(uint32 PartID)
  {
    return GetPart<URobotPart>(PartID);
  };

protected:

  UPROPERTY()
  TMap<uint32, URobotPart*> PartMap;

};

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UPartSingleton : public UObject
{
  GENERATED_BODY()

public:

  UPartSingleton();

  UPROPERTY()
  FPartDatabase PartDB;

protected:

  UPROPERTY()
  UPartAssets* PartAssetsBP;

  void InitPartAssetsBP();

  UPROPERTY()
  UManufacturer* DefaultManufacturer;
  UPROPERTY()
  UManufacturer* RedManufacturer;
  UPROPERTY()
  UManufacturer* BlueManufacturer;
  UPROPERTY()
  UManufacturer* GreenManufacturer;
  UPROPERTY()
  UManufacturer* OrangeManufacturer;
  UPROPERTY()
  UManufacturer* PurpleManufacturer;

  void InitManufacturers();

  void InitPartDB();

  TArray<URobotPart*> GetDefaultParts();
	
};
