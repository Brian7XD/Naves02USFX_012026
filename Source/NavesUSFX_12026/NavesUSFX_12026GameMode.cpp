// Copyright Epic Games, Inc. All Rights Reserved.

#include "NavesUSFX_12026GameMode.h"
#include "NavesUSFX_12026Pawn.h"

ANavesUSFX_12026GameMode::ANavesUSFX_12026GameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ANavesUSFX_12026Pawn::StaticClass();
}

