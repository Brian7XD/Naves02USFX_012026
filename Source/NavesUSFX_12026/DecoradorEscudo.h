// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DecoradorEnemigo.h"
#include "DecoradorEscudo.generated.h"

/**
 * 
 */
UCLASS()
class NAVESUSFX_12026_API ADecoradorEscudo : public ADecoradorEnemigo
{
	GENERATED_BODY()

public:
    ADecoradorEscudo();

    virtual void SetEnemigo(AEnemigo* _Enemigo) override;

protected:
 
    float EscudoExtra;

    FTimerHandle TimerHandle_Escudo;

    void RemoverEscudo();
	
};
