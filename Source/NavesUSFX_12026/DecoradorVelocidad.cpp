// Fill out your copyright notice in the Description page of Project Settings.


#include "DecoradorVelocidad.h"
#include "Enemigo.h"
#include "TimerManager.h"

ADecoradorVelocidad::ADecoradorVelocidad()
{
    MultiplicadorVelocidad = 2.0f;
}

void ADecoradorVelocidad::SetEnemigo(AEnemigo* _Enemigo)
{
    Super::SetEnemigo(_Enemigo);

    if (EnemigoBase)
    {
        VelocidadOriginal = EnemigoBase->GetVelocidad();

        EnemigoBase->SetVelocidad(
            VelocidadOriginal * MultiplicadorVelocidad
        );

        GEngine->AddOnScreenDebugMessage(
            -1,
            5.f,
            FColor::Yellow,
            TEXT("Velocidad aumentada")
        );

        GetWorldTimerManager().SetTimer(
            TimerHandle_Velocidad,
            this,
            &ADecoradorVelocidad::RemoverVelocidad,
            5.0f,
            false
        );
    }
}


void ADecoradorVelocidad::RemoverVelocidad()
{
    if (EnemigoBase)
    {
        EnemigoBase->SetVelocidad(VelocidadOriginal);

        GEngine->AddOnScreenDebugMessage(
            -1,
            5.f,
            FColor::Red,
            TEXT("Velocidad normal")
        );
    }

    Destroy();
}
