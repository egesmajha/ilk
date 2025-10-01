// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AStrainActor.h"
#include "Components/StaticMeshComponent.h"
#include "Plantation/APotActor.h"
#include "Net/UnrealNetwork.h"
#include "Components/SceneComponent.h"

// Sets default values
AAStrainActor::AAStrainActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    SetReplicateMovement(true);
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
    StrainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StrainMesh"));
    StrainMesh->SetupAttachment(RootComponent);
    
    AbilitySystemComponent = CreateDefaultSubobject<UStrainAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    StrainAttributeSet = CreateDefaultSubobject<UStrainAttributeSet>(TEXT("StrainAttributes"));
    AbilitySystemComponent->SetIsReplicated(true);
    
}

UAbilitySystemComponent* AAStrainActor::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}



// Called when the game starts or when spawned
void AAStrainActor::BeginPlay()
{
	Super::BeginPlay();

    if (StrainAttributeSet && DataTable)
    {
        if(DataTable)
        {
            StrainAttributeSet->InitializeFromDataTable(DataTable, RowName);

        }
    }

    GrowthData.CurrentGrowth = 0.0f;
    GrowthData.TimeElapsed = 0.0f;
    GrowthData.bIsMature = false;
}

void AAStrainActor::StartGrowth(AAPotActor* InPot)
{
    OWningPot = InPot;
    GrowthData.CurrentGrowth = 0.0f;
    GrowthData.TimeElapsed = 0.0f;
    GrowthData.bIsMature = false;
}

void AAStrainActor::OnFullyGrown()
{
}

void AAStrainActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AAStrainActor, GrowthData);
}

// Called every frame
void AAStrainActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (!StrainAttributeSet) return;

    float TotalGrowthTime = StrainAttributeSet->GetGrowthTime();
    if (TotalGrowthTime <= 0.f) return;
  
    GrowthData.GrowthTime = TotalGrowthTime;
    GrowthData.CurrentGrowth += (DeltaTime / TotalGrowthTime);
    GrowthData.CurrentGrowth = FMath::Clamp(GrowthData.CurrentGrowth, 0.0f, 1.0f);
    if (GrowthData.CurrentGrowth >= 1.0f && !GrowthData.bIsMature)
    {
        OnFullyGrown();
    }
    

    if (HasAuthority() && !GrowthData.bIsMature) {
        GrowthData.TimeElapsed += DeltaTime;

        float EffectiveGrowthRate = GrowthData.GrowthRate * GrowthData.TemperatureMultiplier * GrowthData.HumidityMultiplier * GrowthData.FertilizerMultiplier * GrowthData.LightMultiplier;

        GrowthData.CurrentGrowth += EffectiveGrowthRate * DeltaTime;

        float MaxGrowth = StrainAttributeSet ? StrainAttributeSet->GetGrowthTime() : 100.0f;
        if (GrowthData.CurrentGrowth >= MaxGrowth) {
            GrowthData.CurrentGrowth = MaxGrowth;
            GrowthData.bIsMature = true;
        }

    }

}

