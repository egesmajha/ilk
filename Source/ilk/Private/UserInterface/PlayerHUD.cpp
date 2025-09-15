// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PlayerHUD.h"
#include "UserInterface/MainMenu.h"
#include "UserInterface/Interaction/InteractionWidget.h"

APlayerHUD::APlayerHUD()
{
}

void APlayerHUD::BeginPlay()
{
    Super::BeginPlay();

    if (MainMenuClass)
    {
        MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
        MainMenuWidget->AddToViewport(5);
        MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
    }

    if (InteractionWidgetClass)
    {
        InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
        InteractionWidget->AddToViewport(-1);
        InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
    }

}

void APlayerHUD::DispalyMenu()
{
    if(MainMenuWidget)
    {
        bIsMainMenuVisible = true;
        MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
        
    }
}


void APlayerHUD::HideMenu()
{

    if (MainMenuWidget)
    {
        bIsMainMenuVisible = false;
        MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);

    }
}


void APlayerHUD::ShowInteractionWidget()
{
    if (InteractionWidget)
    {
        InteractionWidget->SetVisibility(ESlateVisibility::Visible);
    }
}


void APlayerHUD::HideInteractionWidget()
{
    if (InteractionWidget)
    {
        InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
}


void APlayerHUD::UpdateInteractionWidget(const FInteractableData* InteractableData)
{
    if(InteractionWidget)
    {
        if(InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
        {
            InteractionWidget->SetVisibility(ESlateVisibility::Visible);
        }
        InteractionWidget->UpdateWidget(InteractableData);
    }
}
