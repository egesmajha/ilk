// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/UGeneticAlgorithmManager.h"

void UGeneticAlgorithmManager::CrossBreed(UStrainAttributeSet* ParentA, UStrainAttributeSet* ParentB, UStrainAttributeSet*& OutChild)
{

    if (!ParentA || !ParentB || !OutChild) return;

    // Basit örnek: ortalama + küçük random mutasyon
    OutChild->THC.SetBaseValue((ParentA->THC.GetCurrentValue() + ParentB->THC.GetCurrentValue()) / 2.f + FMath::RandRange(-1.f, 1.f));
    OutChild->CBD.SetBaseValue((ParentA->CBD.GetCurrentValue() + ParentB->CBD.GetCurrentValue()) / 2.f + FMath::RandRange(-1.f, 1.f));
    OutChild->Yield.SetBaseValue((ParentA->Yield.GetCurrentValue() + ParentB->Yield.GetCurrentValue()) / 2.f);
    OutChild->TempResistance.SetBaseValue(FMath::Max(ParentA->TempResistance.GetCurrentValue(), ParentB->TempResistance.GetCurrentValue()));
    OutChild->HumidityResistance.SetBaseValue(FMath::Max(ParentA->HumidityResistance.GetCurrentValue(), ParentB->HumidityResistance.GetCurrentValue()));
    OutChild->IndicaRatio.SetBaseValue((ParentA->IndicaRatio.GetCurrentValue() + ParentB->IndicaRatio.GetCurrentValue()) / 2.f);
    OutChild->SativaRatio.SetBaseValue(100.f - OutChild->IndicaRatio.GetCurrentValue());
}