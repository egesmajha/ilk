// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated);

class UItemBase;

UENUM(BlueprintType)
enum class EItemAddResult : uint8
{
    IAR_NoItemAdded UMETA(DisplayName = "No Items Added"),
    IAR_AllItemAdded UMETA(DisplayName = "All Items Added"),
    IAR_PartialAmountItemAdded UMETA(DisplayName = "Some Items Added")
};

USTRUCT(BlueprintType)
struct FItemAddResult
{
    GENERATED_BODY()


    FItemAddResult() :
        ActualAmountAdded(0),
        OperationResult(EItemAddResult::IAR_NoItemAdded),
        ResultMessage(FText::GetEmpty()) { };
  

    // The actual number of items added to the inventory
    UPROPERTY(BlueprintReadOnly, Category = "Item Add Resultt")
    int32 ActualAmountAdded;

    // The result of the add operation
    UPROPERTY(BlueprintReadOnly, Category = "Item Add Resultt")
    EItemAddResult OperationResult;

    // A message providing additional context about the operation result
    UPROPERTY(BlueprintReadOnly, Category = "Item Add Resultt")
    FText ResultMessage;

    static FItemAddResult AddedNone(const FText& ErrorText)
    {
        FItemAddResult AddedNoneResult;
        AddedNoneResult.ActualAmountAdded = 0;
        AddedNoneResult.OperationResult = EItemAddResult::IAR_NoItemAdded;
        AddedNoneResult.ResultMessage = ErrorText;
        return AddedNoneResult;
    }

    static FItemAddResult AddedPartial(const int32 PartialAmountAdded, const FText& ErrorText)
    {
        FItemAddResult AddedPartialResult;
        AddedPartialResult.ActualAmountAdded = PartialAmountAdded;
        AddedPartialResult.OperationResult = EItemAddResult::IAR_PartialAmountItemAdded;
        AddedPartialResult.ResultMessage = ErrorText;
        return AddedPartialResult;
    }
    static FItemAddResult AddedAll(const int32 AllAmountAdded, const FText& ErrorText)
    {
        FItemAddResult AddedAllResult;
        AddedAllResult.ActualAmountAdded = AllAmountAdded;
        AddedAllResult.OperationResult = EItemAddResult::IAR_AllItemAdded;
        AddedAllResult.ResultMessage = ErrorText;
        return AddedAllResult;
    }




};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ILK_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
    //PROPERTIES

    FOnInventoryUpdated OnInventoryUpdated;



    //FUNCTIONS
	UInventoryComponent();

    UFUNCTION(Category = "Inventory")
    FItemAddResult HandleAddItem(UItemBase* InputItem);

    UFUNCTION(Category = "Inventory")
    UItemBase* FindMatchingItem(UItemBase* ItemIn) const;

    UFUNCTION(Category = "Inventory")
    UItemBase* FindNextItemByID(UItemBase* ItemIn) const;

    UFUNCTION(Category = "Inventory")
    UItemBase* FindNextPartialStack(UItemBase* ItemIn) const;
 



    UFUNCTION(Category = "Inventory")
    void RemoveSingleInstanceOfItem(UItemBase* ItemToRemove);

    UFUNCTION(Category = "Inventory")
    int32 RemoveAmountOfItem(UItemBase* ItemIn, const int32 DesiredAmountToRemove);

    UFUNCTION(Category = "Inventory")
    void SplitExistingStack(UItemBase* ItemIn, const int32 AmountToSplit);


    //GETTERS
    UFUNCTION(Category = "Inventory")
    FORCEINLINE float GetInventoryTotalWeight() const { return InventoryTotalWeight; };

    UFUNCTION(Category = "Inventory")
    FORCEINLINE float GetWeightCapacity() const { return InventoryWeightCapacity; };

    UFUNCTION(Category = "Inventory")
    FORCEINLINE int32 GetSlotsCapacity() const { return InventorySlotsCapacity; };

    UFUNCTION(Category = "Inventory")
    FORCEINLINE TArray<UItemBase*> GetInventoryContents() const { return InventoryContents; };

    //SETTERS
    UFUNCTION(Category = "Inventory")
    FORCEINLINE void SetSlotsCapacity(const int32 NewSlotsCapacity) { InventorySlotsCapacity = NewSlotsCapacity; };

    UFUNCTION(Category = "Inventory")
    FORCEINLINE void SetWeightCapacity(const float NewWeightCapacity) { InventoryWeightCapacity = NewWeightCapacity; };

protected:

    //PROPERTIES
    UPROPERTY(VisibleAnywhere, Category = "Inventory")
    float InventoryTotalWeight;

    UPROPERTY(EditInstanceOnly, Category = "Inventory")
    int32 InventorySlotsCapacity;

    UPROPERTY(EditInstanceOnly, Category = "Inventory")
    float InventoryWeightCapacity;

    UPROPERTY(VisibleAnywhere, Category = "Inventory")
    TArray<TObjectPtr<UItemBase>> InventoryContents;




//FUNCTIONS
    virtual void BeginPlay() override;

	FItemAddResult HandleNonStackableItems(UItemBase* InputItem);
    int32 HandleStackableItems(UItemBase* InputItem, int32 RequsetedAddAmount);
    int32 CalculateWeightAddAmount(UItemBase* ItemIn, int32 RequsetedAddAmount);
    int32 CalculateNumberForFullStack(UItemBase* StackableItem, int32 InitialRequsetedAddAmount) ;

    void AddNewItem(UItemBase* Item, const int32 AmountToAdd);
};
