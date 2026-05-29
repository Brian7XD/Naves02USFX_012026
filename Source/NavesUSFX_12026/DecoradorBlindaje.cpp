// Fill out your copyright notice in the Description page of Project Settings.


#include "DecoradorBlindaje.h"
#include "Enemigo.h"
#include "TimerManager.h"

ADecoradorBlindaje::ADecoradorBlindaje()
{
    BlindajeExtra = 20.0f;
}

void ADecoradorBlindaje::SetEnemigo(AEnemigo* _Enemigo)
{
    Super::SetEnemigo(_Enemigo);

    if (EnemigoBase)
    {
        EnemigoBase->SetBlindaje(
            EnemigoBase->GetBlindaje() + BlindajeExtra
        );

        GEngine->AddOnScreenDebugMessage(
            -1,
            5.f,
            FColor::Green,
            TEXT("Blindaje aplicado")
        );

        GetWorldTimerManager().SetTimer(
            TimerHandle_Blindaje,
            this,
            &ADecoradorBlindaje::RemoverBlindaje,
            5.0f,
            false
        );
    }
}

void ADecoradorBlindaje::RemoverBlindaje()
{
    if (EnemigoBase)
    {
        EnemigoBase->SetBlindaje(
            FMath::Max(
                0.0f,
                EnemigoBase->GetBlindaje() - BlindajeExtra
            )
        );

        GEngine->AddOnScreenDebugMessage(
            -1,
            5.f,
            FColor::Red,
            TEXT("Blindaje removido")
        );
    }

    Destroy();
}