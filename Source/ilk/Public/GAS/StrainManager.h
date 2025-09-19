// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "StrainAttributeSet.h"
#include "GeneticAlgorithmManager.h"
#include "StrainManager.generated.h"

/**
 * 
 */
UCLASS()
class ILK_API UStrainManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadOnly, Category = "Database")
    TArray<UStrainAttributeSet*> AllStrains; 

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    UStrainAttributeSet* BreedStrains(UStrainAttributeSet* ParentA, UStrainAttributeSet* ParentB);
};
