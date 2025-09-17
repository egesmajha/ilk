// Fill out your copyright notice in the Description page of Project Settings.
#include "UserInterface/Inventory/InventoryItemSlot.h"
#include "UserInterface/Inventory/InventoryTooltip.h"
#include "UserInterface/Inventory/DragItemVisual.h"
#include "UserInterface/Inventory/InventoryPanel.h"
#include "Items/ItemBase.h"

// engine
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"



void UInventoryItemSlot::NativeOnInitialized()
{
    if (ToolTipClass)
    {
        UInventoryTooltip* ToolTip = CreateWidget<UInventoryTooltip>(this, ToolTipClass);
        ToolTip->InventorySlotBeingHovered = this;
        SetToolTip(ToolTip);
    }
}

void UInventoryItemSlot::NativeConstruct()
{// For additivte brush or color
    Super::NativeConstruct();   
    ItemIcon->SetBrushFromTexture(ItemReference->AssetData.Icon);

    if (ItemReference->NumericData.bIsStackable)
    {
        ItemQuantitiy->SetText(FText::AsNumber(ItemReference->Quantity));
    }
    else
    {
        ItemQuantitiy->SetVisibility(ESlateVisibility::Collapsed);
    }

}

FReply UInventoryItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    return FReply::Handled();
}

void UInventoryItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
}

void UInventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
}

bool UInventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    return false;
}