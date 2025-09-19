// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/StrainManager.h"

UStrainAttributeSet* UStrainManager::BreedStrains(UStrainAttributeSet* ParentA, UStrainAttributeSet* ParentB)
{
    if (!ParentA || !ParentB) return nullptr;
    UStrainAttributeSet* NewStrain = NewObject<UStrainAttributeSet>(this, UStrainAttributeSet::StaticClass());

    UGeneticAlgorithmManager::CrossBreed(ParentA, ParentB, NewStrain);


    AllStrains.Add(NewStrain);

    return NewStrain;
}