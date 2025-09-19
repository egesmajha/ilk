// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "Data/ItemDataStructs.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "StrainAttributeSet.generated.h"
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_MULTICAST_DELEGATE_FourParams(FOnAttributeChangeDelegate, const FGameplayAttribute& /*Attribute*/, float /*NewValue*/, float /*OldValue*/, UObject* /*SourceObject*/);

/**
 * 
 */
UCLASS()
class ILK_API UStrainAttributeSet : public UAttributeSet
{
	GENERATED_BODY()


public:
    UStrainAttributeSet();

    UPROPERTY(BlueprintReadOnly, Category = "Genetics", ReplicatedUsing = OnRep_THC)
    FGameplayAttributeData THC;
    ATTRIBUTE_ACCESSORS(UStrainAttributeSet, THC)


        UPROPERTY(BlueprintReadOnly, Category = "Genetics", ReplicatedUsing = OnRep_CBD)
    FGameplayAttributeData CBD;
    ATTRIBUTE_ACCESSORS(UStrainAttributeSet, CBD)

        UPROPERTY(BlueprintReadOnly, Category = "Genetics", ReplicatedUsing = OnRep_Yield)
    FGameplayAttributeData Yield;
    ATTRIBUTE_ACCESSORS(UStrainAttributeSet, Yield)

        UPROPERTY(BlueprintReadOnly, Category = "Genetics", ReplicatedUsing = OnRep_TempResistance)
    FGameplayAttributeData TempResistance;
    ATTRIBUTE_ACCESSORS(UStrainAttributeSet, TempResistance)

        UPROPERTY(BlueprintReadOnly, Category = "Genetics", ReplicatedUsing = OnRep_HumidityResistance)
    FGameplayAttributeData HumidityResistance;
    ATTRIBUTE_ACCESSORS(UStrainAttributeSet, HumidityResistance)

        UPROPERTY(BlueprintReadOnly, Category = "Genetics", ReplicatedUsing = OnRep_IndicaRatio)
    FGameplayAttributeData IndicaRatio;
    ATTRIBUTE_ACCESSORS(UStrainAttributeSet, IndicaRatio)

        UPROPERTY(BlueprintReadOnly, Category = "Genetics", ReplicatedUsing = OnRep_SativaRatio)
    FGameplayAttributeData SativaRatio;
    ATTRIBUTE_ACCESSORS(UStrainAttributeSet, SativaRatio)


        UFUNCTION(BlueprintCallable, Category = "Strain")
    void InitializeFromDataTable(UDataTable* DataTable, FName RowName);

   
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



protected:
    UFUNCTION()
    void OnRep_THC(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_CBD(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Yield(const FGameplayAttributeData& OldValue);
    
    UFUNCTION()
    void OnRep_TempResistance(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_HumidityResistance(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_IndicaRatio(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_SativaRatio(const FGameplayAttributeData& OldValue);
};
