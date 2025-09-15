// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDataStructs.h"
#include "Character/ilkCharacter.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class ILK_API UItemBase : public UObject
{
	GENERATED_BODY()


public:

    //PROPERTIES AND VARIABLES

    //UPROPERTY()
   //UInventoryComponent* OwningInventory;

    UPROPERTY(VisibleAnywhere, Category = "ItemData", meta = (UIMin=1, UIMax=100))
    int32 Quantity;

    UPROPERTY(EditAnywhere, Category = "ItemData")
    FName ID;

    UPROPERTY(EditAnywhere, Category = "ItemData")
    EItemType ItemType;

    UPROPERTY(EditAnywhere, Category = "ItemData")
    FItemStatics Statics;

    UPROPERTY(EditAnywhere, Category = "ItemData")
    FItemTextData TextData;

    UPROPERTY(EditAnywhere, Category = "ItemData")
    FItemNumericData NumericData;

    UPROPERTY(EditAnywhere, Category = "ItemData")
    FItemAssetData AssetData;

    //FUNCTIONS
    UItemBase();


    UFUNCTION(Category = "Item")
    UItemBase* CharacterItemCopy() const;

    UFUNCTION(Category = "Item")
    FORCEINLINE float GetItemStackWeight() const { return Quantity * NumericData.Weight; };

    UFUNCTION(Category = "Item")
    FORCEINLINE float GetItemSingleWeight() const { return NumericData.Weight; };

    UFUNCTION(Category = "Item")
    FORCEINLINE bool IsFullItemStack() const { return Quantity == NumericData.MaxStackSize; };

    UFUNCTION(Category = "Item")
    void SetQuantity(const int32 NewQuantity);

    virtual void Use(AilkCharacter* Character);
protected:

    bool operator==(const FName& OtherID) const
    {
        return ID == OtherID;
    }
};
