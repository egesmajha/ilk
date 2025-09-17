// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"


UENUM()
enum class EItemQuality : uint8
{
    Shoddy UMETA(DisplayName = "Shoddy"),
    Common UMETA(DisplayName = "Common"),
    Quality UMETA(DisplayName = "Quality"),
    Masterwork UMETA(DisplayName = "Masterwork"),
    Grandmaster UMETA(DisplayName = "Grandmaster")
};

UENUM()
enum class EItemType : uint8
{
    Weed        UMETA(DisplayName = "Weed"),
    Cash         UMETA(DisplayName = "Cash"),
    Drug        UMETA(DisplayName = "Drug"),
    Medical     UMETA(DisplayName = "Medical"),
    Food        UMETA(DisplayName = "Food"),
    Weapon      UMETA(DisplayName = "Weapon"),
    Ammo        UMETA(DisplayName = "Ammo"),
    Mundane   UMETA(DisplayName = "Mundane"),
};

USTRUCT()
struct FItemStatics
{
    GENERATED_BODY()
    //ITEM STATICS ADDED HERE
    UPROPERTY(EditAnywhere)
    float Quality;

    UPROPERTY(EditAnywhere)
    float SellValue;
    
    


};

USTRUCT()
struct FItemTextData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    FText Name;
    UPROPERTY(EditAnywhere)
    FText Description;
    UPROPERTY(EditAnywhere)
    FText InteractionText;
};

USTRUCT()
struct FItemAssetData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere)
    UStaticMesh* Mesh;
};

USTRUCT()
struct FItemNumericData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    int32 MaxStackSize;
    UPROPERTY(EditAnywhere)
    float Weight;
    UPROPERTY(EditAnywhere)
    bool bIsStackable;
};

USTRUCT()
struct FItemData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "ItemData")
    FName ID;

    UPROPERTY(EditAnywhere,Category ="ItemData")
    EItemType ItemType;


    UPROPERTY(EditAnywhere, Category = "ItemData")
    FItemStatics Statics;

    UPROPERTY(EditAnywhere, Category = "Item Data")
    EItemQuality ItemQuality;

    UPROPERTY(EditAnywhere, Category = "ItemData")
    FItemTextData TextData;

    UPROPERTY(EditAnywhere, Category = "ItemData")
    FItemNumericData NumericData;

    UPROPERTY(EditAnywhere, Category = "ItemData")
    FItemAssetData AssetData;




};
