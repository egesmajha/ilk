// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

class UMainMenu;
class UInteractionWidget;
struct FInteractableData;
/**
 * 
 */
UCLASS()
class ILK_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

public:

    //PROPERTIES and VARIABLES
    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
    TSubclassOf<UMainMenu> MainMenuClass;

    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
    TSubclassOf<UInteractionWidget> InteractionWidgetClass;
	
    bool bIsMainMenuVisible;

    //FUNCTIONS

    APlayerHUD();

    void DispalyMenu();
    void HideMenu();

    void ShowInteractionWidget();
    void HideInteractionWidget();
    void UpdateInteractionWidget(const FInteractableData* InteractableData);

protected:
    //PROPERTIES and VARIABLES

    UPROPERTY()
    UMainMenu* MainMenuWidget;

    UPROPERTY()
    UInteractionWidget* InteractionWidget;


    //FUNCTIONS
    virtual void BeginPlay() override;
};
