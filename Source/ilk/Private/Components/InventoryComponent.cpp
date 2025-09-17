// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "Items/ItemBase.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();
}


UItemBase* UInventoryComponent::FindMatchingItem(UItemBase* ItemIn) const
{
    if (ItemIn)
    {
        if(InventoryContents.Contains(ItemIn))
        {
            return ItemIn;
        }
        return nullptr;
    }
    return nullptr;
}




UItemBase* UInventoryComponent::FindNextItemByID(UItemBase* ItemIn) const
{
    if (ItemIn)
    {
        if (const TArray<TObjectPtr<UItemBase>>::ElementType* Result = InventoryContents.FindByKey(ItemIn))
        {
            return *Result;
        }
    }
    return nullptr;
}

UItemBase* UInventoryComponent::FindNextPartialStack(UItemBase* ItemIn) const
{
    if (const TArray<TObjectPtr<UItemBase>>::ElementType* Result =
        InventoryContents.FindByPredicate([&ItemIn](const UItemBase* InventoryItem)
            {
                return InventoryItem->ID == ItemIn->ID && !InventoryItem->IsFullItemStack();
            }
        ))
    {
        return *Result;
    }
    return nullptr;
}

int32 UInventoryComponent::CalculateWeightAddAmount(UItemBase* ItemIn, int32 RequsetedAddAmount)
{
    const int32 WeightMaxAddAmount = FMath::FloorToInt((GetWeightCapacity() - InventoryTotalWeight) / ItemIn->GetItemSingleWeight());
    if(WeightMaxAddAmount >= RequsetedAddAmount)
    {
        return RequsetedAddAmount;
    }
    return WeightMaxAddAmount;
}

int32 UInventoryComponent::CalculateNumberForFullStack(UItemBase* StackableItem, int32 InitialRequsetedAddAmount)
{
    const int32 AddAmountToMakeFullStack = StackableItem->NumericData.MaxStackSize - StackableItem->Quantity;

    return FMath::Min(InitialRequsetedAddAmount, AddAmountToMakeFullStack);
}


void UInventoryComponent::RemoveSingleInstanceOfItem(UItemBase* ItemToRemove)
{
    InventoryContents.RemoveSingle(ItemToRemove);
    OnInventoryUpdated.Broadcast();
}

int32 UInventoryComponent::RemoveAmountOfItem(UItemBase* ItemIn, const int32 DesiredAmountToRemove)
{
    const int32 ActualAmountRemoved = FMath::Min(DesiredAmountToRemove, ItemIn->Quantity);
    ItemIn->SetQuantity(ItemIn->Quantity - ActualAmountRemoved);
    InventoryTotalWeight -= ActualAmountRemoved * ItemIn->GetItemSingleWeight();

    OnInventoryUpdated.Broadcast();
    return ActualAmountRemoved;
}

void UInventoryComponent::SplitExistingStack(UItemBase* ItemIn, const int32 AmountToSplit)
{
    if (!(InventoryContents.Num() + 1 > InventorySlotsCapacity))
    {
        RemoveAmountOfItem(ItemIn, AmountToSplit);
        AddNewItem(ItemIn, AmountToSplit);
    }
}





FItemAddResult UInventoryComponent::HandleNonStackableItems(UItemBase* InputItem)
{ 
    //Check if input item has valid weight
    if(FMath::IsNearlyZero(InputItem->GetItemStackWeight()) || InputItem->GetItemStackWeight() < 0)
    {
        return FItemAddResult::AddedNone(FText::Format(FText::FromString("Could not add {0} to the inventory. Item has invalid Weight value"), InputItem->TextData.Name));
    }

    //Will the item weigt overflow the inventory weight capacity
    if (InventoryTotalWeight + InputItem->GetItemSingleWeight() > GetWeightCapacity())
    {
        return FItemAddResult::AddedNone(FText::Format(FText::FromString("Could not add {0} to the inventory. Item would overflow Weight limit"),InputItem->TextData.Name));
    }

    if(InventoryContents.Num() + 1 > InventorySlotsCapacity)
    {
        return FItemAddResult::AddedNone(FText::Format(FText::FromString("Could not add {0} to the inventory. Inventory slots are full"), InputItem->TextData.Name));
    }

    AddNewItem(InputItem, 1);
    return FItemAddResult::AddedAll(
        1, FText::Format(FText::FromString("Successfully added a single {0} to the inventory."), InputItem->TextData.Name));
 }

int32 UInventoryComponent::HandleStackableItems(UItemBase* InputItem, int32 RequsetedAddAmount)
{
    return 0;
}

FItemAddResult UInventoryComponent::HandleAddItem(UItemBase* InputItem)
{
    if (GetOwner())
    {
        const int32 InitialRequestedAddAmount = InputItem->Quantity;

        // Handle nonstackable items
        if (!InputItem->NumericData.bIsStackable)
        {
            return  HandleNonStackableItems(InputItem);
        }


        // Handle stackable items
        const int32 StackableAmountAdded = HandleStackableItems(InputItem, InitialRequestedAddAmount);

        if (StackableAmountAdded == InitialRequestedAddAmount)
        {
            return FItemAddResult::AddedAll(InitialRequestedAddAmount,
                FText::Format(FText::FromString(" Successfully added {0} {1} to the inventory."),
                InitialRequestedAddAmount,
                InputItem->TextData.Name));
        }

        if(StackableAmountAdded < InitialRequestedAddAmount && StackableAmountAdded > 0)
        {
            return FItemAddResult::AddedPartial(StackableAmountAdded,
                FText::Format(FText::FromString(" Only partial amount of {0} added to inventory. Numbers added : {1}"),
                StackableAmountAdded,
                InputItem->TextData.Name,
                InitialRequestedAddAmount
                    ));
        }

        if(StackableAmountAdded <= 0)
        { return FItemAddResult::AddedNone(
            FText::Format(FText::FromString("Could not add {0} to the inventory. Inventory full or would overflow weight limit"),
                InputItem->TextData.Name));
        }
    }
    check(false);   
    return FItemAddResult::AddedNone(FText::FromString("Could not add item to the inventory. Inventory has no valid owner"));
}


void UInventoryComponent::AddNewItem(UItemBase* Item, const int32 AmountToAdd)
{

    UItemBase* NewItem;

    if (Item->bIsCopy || Item->bIsPickup)
    {

        //if the item is already a copy or a pickup,
        NewItem = Item;
        NewItem->ResetItemFlags();
    }
    else {

        //when used splitting or draggin to another inventory
        NewItem = Item->CreateItemCopy();
    }

    NewItem->OwningInventory = this;
    NewItem->SetQuantity(AmountToAdd);

    InventoryContents.Add(NewItem);
    InventoryTotalWeight += NewItem->GetItemStackWeight();
    OnInventoryUpdated.Broadcast();
}



