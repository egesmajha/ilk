// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AStrainActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AAStrainActor::AAStrainActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
    StrainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StrainMesh"));
    StrainMesh->SetupAttachment(RootComponent);
    
    AbilitySystemComponent = CreateDefaultSubobject<UStrainAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    StrainAttributeSet = CreateDefaultSubobject<UStrainAttributeSet>(TEXT("StrainAttributes"));
}

UAbilitySystemComponent* AAStrainActor::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AAStrainActor::BeginPlay()
{
	Super::BeginPlay();

    if (StrainAttributeSet)
    {
        if(DataTable)
        {
            StrainAttributeSet->InitializeFromDataTable(DataTable, RowName);

        }
    }
}

// Called every frame
void AAStrainActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    /*if (AbilitySystemComponent && StrainAttributeSet) {
        float GrowthTime = StrainAttributeSet->GetGrowthTime();
        float CurrentGrowth = StrainAttributeSet->GetCurrentGrowth();

        if (CurrentGrowth < GrowthTime)
        {
            StrainAttributeSet->SetCurrentGrowth(CurrentGrowth + DeltaTime);
        }
        else { UE_LOG(LogTemp, Warning, TEXT("Plant %s fully grown!"), *GetName()); }
    }*/

    if (!GrowthData.bIsMature) {
        GrowthData.TimeElapsed += DeltaTime;

        float EffectiveGrowthRate = GrowthData.GrowthRate * GrowthData.TemperatureMultiplier * GrowthData.HumidityMultiplier * GrowthData.FertilizerMultiplier * GrowthData.LightMultiplier;

        GrowthData.CurrentGrowth += EffectiveGrowthRate * DeltaTime;

        if (GrowthData.CurrentGrowth >= 100.0f) {
            GrowthData.CurrentGrowth = 100.0f;
            GrowthData.bIsMature = true;
        }

    }

}

