// Copyright Epic Games, Inc. All Rights Reserved.

#include "TrisePlayerController.h"

ATrisePlayerController::ATrisePlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
