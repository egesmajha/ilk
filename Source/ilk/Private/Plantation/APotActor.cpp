// Fill out your copyright notice in the Description page of Project Settings.


#include "Plantation/APotActor.h"

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

    if (PlantClass)
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

