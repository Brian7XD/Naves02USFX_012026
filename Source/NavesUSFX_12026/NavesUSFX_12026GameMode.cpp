// Copyright Epic Games, Inc. All Rights Reserved.

#include "NavesUSFX_12026GameMode.h"
#include "NavesUSFX_12026Pawn.h"


void ANavesUSFX_12026GameMode::BeginPlay()
{
    Super::BeginPlay();

    FachadaEnemigos = GetWorld()->SpawnActor<AFacadeNaves>(AFacadeNaves::StaticClass(),
    FVector::ZeroVector,
    FRotator::ZeroRotator
    );

    if (FachadaEnemigos)
    {
        FachadaEnemigos->IniciarAtaques();
    }
}

