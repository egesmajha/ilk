#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"

UENUM()
enum class EItemType : uint8
{
    Weed        UMETA(DisplayName = "Weed"),
    Cash         UMETA(DisplayName = "Cash"),
    Mundane   UMETA(DisplayName = "Mundane"),
};

USTRUCT()
struct FItemStatics
{
    GENERATED_USTRCUT_BODY()

    UPROPERTY(EditAnywhere)
    float Amount;


};

USTRUCT()
struct FItemTextData
{
    GENERATED_USTRCUT_BODY()

    UPROPERTY(EditAnywhere)
    FText Name;
    UPROPERTY(EditAnywhere)
    FText Description;
    UPROPERTY(EditAnywhere)
    FText InteractionText;
    UPROPERTY(EditAnywhere)
    FText InteractionText;
};;


USTRUCT()
struct FItemData : public FTableRowBase
{
    GENERATED_USTRCUT_BODY()
};
