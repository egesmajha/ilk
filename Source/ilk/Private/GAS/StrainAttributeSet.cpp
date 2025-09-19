 // Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/StrainAttributeSet.h"
#include "Net/UnrealNetwork.h"


UStrainAttributeSet::UStrainAttributeSet()
{
    // Initialize default values for attributes
    //THC.SetBaseValue(0.f);
    //THC.SetCurrentValue(0.f);
    //CBD.SetBaseValue(0.f);
    //CBD.SetCurrentValue(0.f);
    //Yield.SetBaseValue(0.f);
    //Yield.SetCurrentValue(0.f);
    //TempResistance.SetBaseValue(0.f);
    //TempResistance.SetCurrentValue(0.f);
    //HumidityResistance.SetBaseValue(0.f);
    //HumidityResistance.SetCurrentValue(0.f);
    //IndicaRatio.SetBaseValue(0.f);
    //IndicaRatio.SetCurrentValue(0.f);
    //SativaRatio.SetBaseValue(0.f);
    //SativaRatio.SetCurrentValue(0.f);
}


void UStrainAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const  
{  
   Super::GetLifetimeReplicatedProps(OutLifetimeProps);  

   // Ensure the CBD property is marked as replicated and accessible  
   DOREPLIFETIME_CONDITION_NOTIFY(UStrainAttributeSet, THC, COND_None, REPNOTIFY_Always);  
   DOREPLIFETIME_CONDITION_NOTIFY(UStrainAttributeSet, CBD, COND_None, REPNOTIFY_Always);  
   DOREPLIFETIME_CONDITION_NOTIFY(UStrainAttributeSet, Yield, COND_None, REPNOTIFY_Always);  
   DOREPLIFETIME_CONDITION_NOTIFY(UStrainAttributeSet, TempResistance, COND_None, REPNOTIFY_Always);  
   DOREPLIFETIME_CONDITION_NOTIFY(UStrainAttributeSet, HumidityResistance, COND_None, REPNOTIFY_Always);  
   DOREPLIFETIME_CONDITION_NOTIFY(UStrainAttributeSet, IndicaRatio, COND_None, REPNOTIFY_Always);  
   DOREPLIFETIME_CONDITION_NOTIFY(UStrainAttributeSet, SativaRatio, COND_None, REPNOTIFY_Always);  
}    // Ensure the CBD property is properly declared and accessible  
    UCLASS()  
    class ILK_API UStrainAttributeSet : public UAttributeSet  
    {  
       GENERATED_BODY()  

    public:  
       UStrainAttributeSet();  

       // Declare the CBD property as replicated  
       UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_CBD, Category = "Attributes")  
       FGameplayAttributeData CBD;  

       // Replication notification function for CBD  
       UFUNCTION()  
       void OnRep_CBD(const FGameplayAttributeData& OldValue);  

       // Other properties and methods...  
    };

void UStrainAttributeSet::OnRep_THC(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UStrainAttributeSet, THC, OldValue);
}

void UStrainAttributeSet::OnRep_CBD(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UStrainAttributeSet, CBD, OldValue);
}

void UStrainAttributeSet::OnRep_Yield(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UStrainAttributeSet, Yield, OldValue);
}


void UStrainAttributeSet::OnRep_TempResistance(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UStrainAttributeSet, TempResistance, OldValue);
}


void UStrainAttributeSet::OnRep_HumidityResistance(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UStrainAttributeSet, HumidityResistance, OldValue);
}


void UStrainAttributeSet::OnRep_IndicaRatio(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UStrainAttributeSet, IndicaRatio, OldValue);
}


void UStrainAttributeSet::OnRep_SativaRatio(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UStrainAttributeSet, SativaRatio, OldValue);
}

void UStrainAttributeSet::InitializeFromDataTable(UDataTable* DataTable, FName RowName) {
    if (!DataTable) return;

    FStrainDataRow* Row = DataTable->FindRow<FStrainDataRow>(RowName, TEXT(""));
    if (!Row) return;

    THC.SetBaseValue(Row->THC);
    THC.SetCurrentValue(Row->THC);

    CBD.SetBaseValue(Row->CBD);
    CBD.SetCurrentValue(Row->CBD);

    Yield.SetBaseValue(Row->Yield);
    Yield.SetCurrentValue(Row->Yield);

    TempResistance.SetBaseValue(Row->TempResistance);
    TempResistance.SetCurrentValue(Row->TempResistance);

    HumidityResistance.SetBaseValue(Row->HumidityResistance);
    HumidityResistance.SetCurrentValue(Row->HumidityResistance);

    IndicaRatio.SetBaseValue(Row->IndicaRatio);
    IndicaRatio.SetCurrentValue(Row->IndicaRatio);

    SativaRatio.SetBaseValue(Row->SativaRatio);
    SativaRatio.SetCurrentValue(Row->SativaRatio);
}


