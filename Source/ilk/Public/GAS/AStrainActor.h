// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GAS/StrainAbilitySystemComponent.h"
#include "GAS/StrainAttributeSet.h"
#include "AbilitySystemInterface.h" 
#include "AbilitySystemComponent.h"
#include "AStrainActor.generated.h"

UCLASS()
class ILK_API AAStrainActor : public AActor
{
	GENERATED_BODY()
	


public:	
	// Sets default values for this actor's properties
	AAStrainActor();
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
    UAbilitySystemComponent* AbilitySystemComponent;

    UPROPERTY()
    UStrainAttributeSet* StrainAttributeSet;

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const ;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
