// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GAS/AStrainActor.h"
#include "APotActor.generated.h"

UCLASS()
class ILK_API AAPotActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAPotActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* Root;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* PotMesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
    AAStrainActor* CurrentPlant;

    UFUNCTION(BlueprintCallable, Category = "Pot")
    void PlantSeed(TSubclassOf<AAStrainActor> PlantClass, UDataTable* StrainData, FName StrainRow);
};
