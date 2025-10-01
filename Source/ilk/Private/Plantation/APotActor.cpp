#include "Plantation/APotActor.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AAPotActor::AAPotActor()
{
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);

    PotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PotMesh"));
    PotMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AAPotActor::BeginPlay()
{
    Super::BeginPlay();
}

void AAPotActor::PlantSeed(TSubclassOf<AAStrainActor> PlantClass, UDataTable* StrainData, FName StrainRow)
{
    if (CurrentPlant) return;

    if (PlantClass && HasAuthority()) // Server-only
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        FVector Location = GetActorLocation() + FVector(0.f, 0.f, 50.f);
        FRotator Rotation = FRotator::ZeroRotator;

        CurrentPlant = GetWorld()->SpawnActor<AAStrainActor>(PlantClass, Location, Rotation, SpawnParams);

        if (CurrentPlant)
        {
            CurrentPlant->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

            // DataTable ve RowName’i set et
            CurrentPlant->DataTable = StrainData;
            CurrentPlant->RowName = StrainRow;

            CurrentPlant->StrainAttributeSet->InitializeFromDataTable(StrainData, StrainRow);
            CurrentPlant->StartGrowth(this);
        }
    }
}

void AAPotActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AAPotActor, CurrentPlant);
}