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


   /* UFUNCTION(BlueprintPure, Category = "Strain|Attributes")
    float GetTHC() const { return THC.GetCurrentValue(); }

    UFUNCTION(BlueprintPure, Category = "Strain|Attributes")
    float GetCBD() const { return CBD.GetCurrentValue(); }

    UFUNCTION(BlueprintPure, Category = "Strain|Attributes")
    float GetYield() const { return Yield.GetCurrentValue(); }

    UFUNCTION(BlueprintPure, Category = "Strain|Attributes")
    float GetTempResistance() const { return TempResistance.GetCurrentValue(); }

    UFUNCTION(BlueprintPure, Category = "Strain|Attributes")
    float GetHumidityResistance() const { return HumidityResistance.GetCurrentValue(); }

    UFUNCTION(BlueprintPure, Category = "Strain|Attributes")
    float GetIndicaRatio() const { return IndicaRatio.GetCurrentValue(); }

    UFUNCTION(BlueprintPure, Category = "Strain|Attributes")
    float GetSativaRatio() const { return SativaRatio.GetCurrentValue(); }*/




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
