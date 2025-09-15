// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"

UItemBase::UItemBase()
{
}

UItemBase* UItemBase::CharacterItemCopy() const
{
    UItemBase* ItemCopy = NewObject<UItemBase>(StaticClass());

    ItemCopy->ID = this->ID;    
    ItemCopy->Quantity = this->Quantity;
    ItemCopy->ItemType = this->ItemType;
    ItemCopy->ItemStatics = this->ItemStatics;  
    ItemCopy->TextData = this->TextData;
    ItemCopy->NumericData = this->NumericData;
    ItemCopy->AssetData = this->AssetData;
    
    return ItemCopy;
}

void UItemBase::SetQuantity(const int32 NewQuantity)
{
    if (NewQuantity != Quantity)
    {
        Quantity = FMath::Clamp(NewQuantity, 0,NumericData.bIsStackable ? NumericData.MaxStackSize: 1);

        //if (OwningInventory)
        //{
        //    if (Quantity <= 0)
        // {
        //  owningInventory->RemoveItem(this);
        // }
        //}
    }
}

void UItemBase::Use(AilkCharacter* Character)
{
}
