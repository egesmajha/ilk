// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Inventory/InventoryTooltip.h"
#include "UserInterface/Inventory/InventoryItemSlot.h"
#include "Items/ItemBase.h"



void UInventoryTooltip::NativeConstruct()
{
    Super::NativeConstruct();

    const UItemBase* ItemBeingHovered = InventorySlotBeingHovered->GetItemReference();
    

    switch (ItemBeingHovered->ItemType)
    {
    case EItemType::Mundane:
        ItemType->SetText(FText::FromString("Mundane"));
        UsageText->SetVisibility(ESlateVisibility::Collapsed);
        break;
    case EItemType::Weed:
        ItemType->SetText(FText::FromString("Weed"));
        UsageText->SetVisibility(ESlateVisibility::Collapsed);
        break;
    case EItemType::Weapon:
        ItemType->SetText(FText::FromString("Weapon"));
        break;

    case EItemType::Medical:
        ItemType->SetText(FText::FromString("Medical"));
        break;

    case EItemType::Drug:
        ItemType->SetText(FText::FromString("Drug"));
        UsageText->SetVisibility(ESlateVisibility::Collapsed);
        break;

    case EItemType::Food:   
        ItemType->SetText(FText::FromString("Food"));
        break;
    case EItemType::Ammo:
        ItemType->SetText(FText::FromString("Ammo"));
        break;
    default:;
    }
        ItemName->SetText(ItemBeingHovered->TextData.Name);
        UsageText->SetText(ItemBeingHovered->TextData.InteractionText);
        ItemDescription->SetText(ItemBeingHovered->TextData.Description);
        SellValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatics.SellValue));
        Quality->SetText(FText::AsNumber(ItemBeingHovered->ItemStatics.Quality));
        StackWeight->SetText(FText::AsNumber(ItemBeingHovered->GetItemStackWeight()));


        if (ItemBeingHovered->NumericData.bIsStackable)
        {
            MaxStackSize->SetText(FText::AsNumber(ItemBeingHovered->NumericData.MaxStackSize));
        }
        else
        {
            MaxStackSize->SetVisibility(ESlateVisibility::Collapsed);
        }
   

    
}
