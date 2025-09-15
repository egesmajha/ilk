// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/MainMenu.h"
#include "Character/ilkCharacter.h"

void UMainMenu::NativeOnInitialized()
{
  
  
}

void UMainMenu::NativeConstruct()
{
    PlayerCharacter = Cast<AilkCharacter>(GetOwningPlayerPawn());
}

bool UMainMenu::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    return false;

    //return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
