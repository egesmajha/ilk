// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Pickup.h"
#include "Items/ItemBase.h"


APickup::APickup()
{
 
	PrimaryActorTick.bCanEverTick = false;

    PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
    PickupMesh->SetSimulatePhysics(true);
    SetRootComponent(PickupMesh);
}


// Called when the game starts or when spawned
void APickup::BeginPlay()
{
    Super::BeginPlay();

    InitializePickup(UItemBase::StaticClass(),ItemQuantity);
}




void APickup::InitializePickup(const TSubclassOf<UItemBase> BaseClass, const int32 InQuantity)
{

    if (ItemDataTable && !DesiredItemID.IsNone())
    {
        const FItemData* ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID ,DesiredItemID.ToString());
        
        ItemReferance = NewObject<UItemBase>(this, BaseClass);


        ItemReferance->ID = ItemData->ID;
        ItemReferance->ItemType = ItemData->ItemType;
        ItemReferance->NumericData = ItemData->NumericData;
        ItemReferance->TextData = ItemData->TextData;
        ItemReferance->AssetData = ItemData->AssetData;
        
        InQuantity <= 0 ? ItemReferance->SetQuantity(1) : ItemReferance->SetQuantity(InQuantity);

        PickupMesh->SetStaticMesh(ItemData->AssetData.Mesh);
        UpdateInteractableData();
    }
}

void APickup::InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity)
{
    ItemReferance = ItemToDrop;

    InQuantity <= 0 ? ItemReferance->SetQuantity(1) : ItemReferance->SetQuantity(InQuantity);

    ItemReferance->NumericData.Weight = ItemToDrop->GetItemSingleWeight();
    PickupMesh->SetStaticMesh(ItemToDrop->AssetData.Mesh);

    UpdateInteractableData();
}


void APickup::UpdateInteractableData()
{
    InstanceInteractableData.InteractableType = EInteractableType::Pickup;
    InstanceInteractableData.Action = ItemReferance->TextData.InteractionText;
    InstanceInteractableData.Name = ItemReferance->TextData.Name;
    InstanceInteractableData.Quantity = ItemReferance->Quantity;
    InteractableData = InstanceInteractableData;
}


void APickup::BeginFocus()
{
    if (PickupMesh)
    {
        PickupMesh->SetRenderCustomDepth(true);
    }
}

void APickup::EndFocus()
{
    if (PickupMesh)
    {
        PickupMesh->SetRenderCustomDepth(false);
    }
}



void APickup::Interact(AilkCharacter* PlayerCharacter)
{
    if (PlayerCharacter)
    {
        TakePickup(PlayerCharacter);
    }
}



void APickup::TakePickup(const AilkCharacter* Taker)
{
    if (!IsPendingKillPending())
    {
        if (ItemReferance)
        {
            /*if (UInventroyComponent* PlayerInventory = Taker->GetInventory())*/;

            //Trying to add item to players inv
            //Result of the add
            //adjust or destroy
        }
    }
}

void APickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    const FName ChangedPropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(APickup, DesiredItemID))
    {
        if (ItemDataTable)
        {
            const FString  ContextString{ DesiredItemID.ToString() };

            if (const FItemData* ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString()))
            {
                PickupMesh->SetStaticMesh(ItemData->AssetData.Mesh);
            }
        }
    }
}

