// Copyright Epic Games, Inc. All Rights Reserved.

#include "Gamemode/ilkGameMode.h"
#include "Character/ilkCharacter.h"
#include "UObject/ConstructorHelpers.h"

AilkGameMode::AilkGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
