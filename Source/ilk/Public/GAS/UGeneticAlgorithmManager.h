// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StrainAttributeSet.h"
#include "UGeneticAlgorithmManager.generated.h"

/**
 * 
 */
UCLASS()
class ILK_API UUGeneticAlgorithmManager : public UObject
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Genetics")
    static void CrossBreed(UStrainAttributeSet* ParentA, UStrainAttributeSet* ParentB, UStrainAttributeSet*& OutChild);
};
