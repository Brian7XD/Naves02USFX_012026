// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FacadeNaves.h"
#include "NavesUSFX_12026GameMode.generated.h"

UCLASS(MinimalAPI)
class ANavesUSFX_12026GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		AFacadeNaves* FachadaEnemigos;
};



