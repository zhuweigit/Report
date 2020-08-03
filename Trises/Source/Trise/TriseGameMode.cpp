// Copyright Epic Games, Inc. All Rights Reserved.

#include "TriseGameMode.h"
#include "TrisePlayerController.h"
#include "TrisePawn.h"

ATriseGameMode::ATriseGameMode()
{
	// no pawn by default
	DefaultPawnClass = ATrisePawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ATrisePlayerController::StaticClass();
}
