#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GAS/StrainAbilitySystemComponent.h"
#include "GAS/StrainAttributeSet.h"
#include "AbilitySystemInterface.h" 
#include "AbilitySystemComponent.h"
#include "AStrainActor.generated.h"


UCLASS()
class ILK_API AAStrainActor : public AActor, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    AAStrainActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* StrainMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
    UStrainAbilitySystemComponent* AbilitySystemComponent;

    UPROPERTY()
    UStrainAttributeSet* StrainAttributeSet;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Strain|Data")
    UDataTable* DataTable;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Strain|Data")
    FName RowName;

    UPROPERTY(ReplicatedUsing = OnRep_GrowthData, VisibleAnywhere, BlueprintReadOnly, Category = "Strain|Data")
    FGrowthData GrowthData;

    // Item system
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FItemData ItemInfo;

    UPROPERTY()
    class AAPotActor* OWningPot;

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    UFUNCTION(BlueprintCallable, Category = "Growth")
    void StartGrowth(AAPotActor* InPot);

    UFUNCTION(BlueprintCallable)
    void OnFullyGrown();

    UFUNCTION()
    void OnRep_GrowthData();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    virtual void BeginPlay() override;
public:
    virtual void Tick(float DeltaTime) override;
};