// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"


UItemBase::UItemBase()
{
}
void UItemBase::ResetItemFlags()
{
    bIsCopy = false;
    bIsPickup = false;
}

UItemBase* UItemBase::CreateItemCopy() const
{
    UItemBase* ItemCopy = NewObject<UItemBase>(StaticClass());

    ItemCopy->ID = this->ID;
    ItemCopy->Quantity = this->Quantity;
    ItemCopy->ItemType = this->ItemType;
    ItemCopy->ItemStatics = this->ItemStatics;
    ItemCopy->TextData = this->TextData;
    ItemCopy->NumericData = this->NumericData;
    ItemCopy->AssetData = this->AssetData;
    ItemCopy->bIsCopy = true;

    return ItemCopy;
}

void UItemBase::SetQuantity(const int32 NewQuantity)
{
    if (NewQuantity != this->Quantity)
    {
        Quantity = FMath::Clamp(NewQuantity, 0, this->NumericData.bIsStackable ? this->NumericData.MaxStackSize : 1);
    }
}



void UItemBase::Use(AilkCharacter* Character)
{
}
