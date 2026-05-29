// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DecoradorEnemigo.h"
#include "DecoradorVelocidad.generated.h"

/**
 * 
 */
UCLASS()
class NAVESUSFX_12026_API ADecoradorVelocidad : public ADecoradorEnemigo
{
    GENERATED_BODY()

public:
    ADecoradorVelocidad();

    virtual void SetEnemigo(AEnemigo* _Enemigo) override;

protected:

    float MultiplicadorVelocidad;

    FTimerHandle TimerHandle_Velocidad;

    float VelocidadOriginal;

    void RemoverVelocidad();
};
