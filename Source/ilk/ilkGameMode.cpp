// Copyright Epic Games, Inc. All Rights Reserved.

#include "ilkGameMode.h"
#include "ilkCharacter.h"
#include "UObject/ConstructorHelpers.h"

AilkGameMode::AilkGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
