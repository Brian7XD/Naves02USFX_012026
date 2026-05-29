// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DecoradorEnemigo.h"
#include "DecoradorBlindaje.generated.h"

/**
 * 
 */

UCLASS()
class NAVESUSFX_12026_API ADecoradorBlindaje : public ADecoradorEnemigo
{
    GENERATED_BODY()

public:
    ADecoradorBlindaje();

    virtual void SetEnemigo(AEnemigo* _Enemigo) override;

protected:
    
    float BlindajeExtra;

    FTimerHandle TimerHandle_Blindaje;

    void RemoverBlindaje();
};