// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestCodeProjectGameMode.h"
#include "TestCodeProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestCodeProjectGameMode::ATestCodeProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
