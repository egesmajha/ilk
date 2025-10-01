#include "GAS/AStrainActor.h"
#include "Components/StaticMeshComponent.h"
#include "Plantation/APotActor.h"
#include "Net/UnrealNetwork.h"
#include "Components/SceneComponent.h"

AAStrainActor::AAStrainActor()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    SetReplicateMovement(true);

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    StrainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StrainMesh"));
    StrainMesh->SetupAttachment(Root);

    AbilitySystemComponent = CreateDefaultSubobject<UStrainAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);

    StrainAttributeSet = CreateDefaultSubobject<UStrainAttributeSet>(TEXT("StrainAttributes"));
}

UAbilitySystemComponent* AAStrainActor::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void AAStrainActor::BeginPlay()
{
    Super::BeginPlay();

    if (StrainAttributeSet && DataTable)
    {
        StrainAttributeSet->InitializeFromDataTable(DataTable, RowName);
        GrowthData.GrowthTime = StrainAttributeSet->GetGrowthTime();
    }
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
    GrowthData.bIsMature = true;
    // Buraya ek olarak event veya blueprint trigger ekleyebilirsin
}

void AAStrainActor::OnRep_GrowthData()
{
    // Blueprint veya UI için replication callback
}

void AAStrainActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!StrainAttributeSet || GrowthData.bIsMature) return;

    GrowthData.TimeElapsed += DeltaTime;

    float EffectiveGrowthRate = GrowthData.GrowthRate * GrowthData.TemperatureMultiplier
        * GrowthData.HumidityMultiplier * GrowthData.FertilizerMultiplier * GrowthData.LightMultiplier;

    GrowthData.CurrentGrowth += (DeltaTime / GrowthData.GrowthTime) * EffectiveGrowthRate;
    GrowthData.CurrentGrowth = FMath::Clamp(GrowthData.CurrentGrowth, 0.0f, 1.0f);

    if (GrowthData.CurrentGrowth >= 1.0f)
    {
        OnFullyGrown();
    }
}

void AAStrainActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AAStrainActor, GrowthData);
}