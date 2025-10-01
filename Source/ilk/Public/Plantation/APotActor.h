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

    // Multiplayer uyumlu olması için Replicated ekledik
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Components")
    AAStrainActor* CurrentPlant;

    UFUNCTION(BlueprintCallable, Category = "Pot")
    void PlantSeed(TSubclassOf<AAStrainActor> PlantClass, UDataTable* StrainData, FName StrainRow);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};