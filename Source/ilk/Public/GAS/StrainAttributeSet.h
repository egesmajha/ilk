// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "StrainAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ILK_API UStrainAttributeSet : public UAttributeSet
{
	GENERATED_BODY()


public:
    UPROPERTY(EditAnywhere.BlueprintReadWrite, Category = "Genetics")
    FGameplayAttributeData THC;
    ATTRIBUTE_ACCESSORS(UStrainAttributeSet, THC);

    UPROPERTY(EditAnywhere.BlueprintReadWrite, Category = "Genetics")
    FGameplayAttributeData CBD;
    ATTRIBUTE_ACCESSORS(UStrainAttributeSet, CBD);


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Genetics")
    FGameplayAttributeData Yield;
    ATTRIBUTE_ACCESSORS(UStrainAttributeSet, Yield);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Genetics")
    FGameplayAttributeData TempResistance;
    ATTRIBUTE_ACCESSORS(UStrainAttributeSet, TempResistance);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Genetics")
    FGameplayAttributeData HumidityResistance;
    ATTRIBUTE_ACCESSORS(UStrainAttributeSet, HumidityResistance);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Genetics")
    FGameplayAttributeData IndicaRatio;
    ATTRIBUTE_ACCESSORS(UStrainAttributeSet, IndicaRatio);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Genetics")
    FGameplayAttributeData SativaRatio;
    ATTRIBUTE_ACCESSORS(UStrainAttributeSet, SativaRatio);
};
