// Copyright Epic Games, Inc. All Rights Reserved.

#include "GelotzGameMode.h"
#include "GelotzCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGelotzGameMode::AGelotzGameMode()
{
	numRounds = 1;
	roundTime = 99;
	isTimerActive = false;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
