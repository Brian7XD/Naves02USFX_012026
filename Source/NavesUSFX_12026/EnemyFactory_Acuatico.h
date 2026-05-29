// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyFactory.h"
#include "EnemyFactory_Acuatico.generated.h"

UCLASS()
class NAVESUSFX_12026_API AEnemyFactory_Acuatico : public AEnemyFactory
{
    GENERATED_BODY()

public:
    virtual AEnemigo* CrearEnemigo(
        FVector Posicion,
        FRotator Rotacion
    ) override;
};
