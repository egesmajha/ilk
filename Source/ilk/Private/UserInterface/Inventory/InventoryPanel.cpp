// Fill out your copyright notice in the Description page of Project Settings.

#include "UserInterface/Inventory/InventoryPanel.h"
#include "Character/ilkCharacter.h"
#include "Components/InventoryComponent.h"
#include "UserInterface/Inventory/InventoryItemSlot.h"

void UInventoryPanel::NativeOnInitialized()
{
    PlayerCharacter = Cast<AilkCharacter>(GetOwningPlayerPawn());

    if(PlayerCharacter)
    {
        InventoryReference = PlayerCharacter->GetInventory();

        if(InventoryReference)
        {
            InventoryReference->OnInventoryUpdated.AddUObject(this, &UInventoryPanel::RefreshInventory);
            SetInfoText();

        }
    }
}




void UInventoryPanel::SetInfoText() const
{
    WeightInfo->SetText(FText::Format(FText::FromString("{0}/{1}"),
        InventoryReference->GetInventoryTotalWeight(),
        InventoryReference->GetWeightCapacity()
    ));

    CapacityInfo->SetText(FText::Format(FText::FromString("{0}/{1}"),
        InventoryReference->GetInventoryContents().Num(),
        InventoryReference->GetSlotsCapacity()
    ));
}

void UInventoryPanel::RefreshInventory()
{
    if(InventoryReference && InventorySlotClass)
        {
        InventoryPanel->ClearChildren();

        for(UItemBase* const& InventoryItem : InventoryReference->GetInventoryContents())
        {
            UInventoryItemSlot* ItemSlot = CreateWidget<UInventoryItemSlot>(this, InventorySlotClass);
            ItemSlot->SetItemReference(InventoryItem);
            
            InventoryPanel->AddChildToWrapBox(ItemSlot);
        }

       }
}

bool UInventoryPanel::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    return false;
}
