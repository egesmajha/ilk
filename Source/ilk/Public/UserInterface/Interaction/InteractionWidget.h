// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

class AilkCharacter;
struct FInteractableData;
class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class ILK_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, Category = "Interaction Widget | Player Referance")
    AilkCharacter* PlayerCharacter;

    void UpdateWidget(const FInteractableData* InteractableData);

protected:
    UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Player Referance")
    UTextBlock* NameText;

    UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Player Referance")
    UTextBlock* ActionText;

    UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Player Referance")
    UTextBlock* QuantityText;
     
    UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Player Referance")
    UTextBlock* KeyPressText;

    UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Player Referance")
    UProgressBar* InteractionProgressBar;

    UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Player Referance")
    float CurrentInteractionDuration;

    UFUNCTION(Category = "Interaction Widget | Player Referance")
    float UpdateInteractionProgress();

    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
};
