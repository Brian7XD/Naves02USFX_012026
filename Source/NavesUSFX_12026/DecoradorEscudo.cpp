// Fill out your copyright notice in the Description page of Project Settings.


#include "DecoradorEscudo.h"
#include "Enemigo.h"
#include "TimerManager.h"

ADecoradorEscudo::ADecoradorEscudo()
{
    EscudoExtra = 50.0f;
}

void ADecoradorEscudo::SetEnemigo(AEnemigo* _Enemigo)
{
    Super::SetEnemigo(_Enemigo);

    if (EnemigoBase)
    {
        EnemigoBase->SetEscudo(
            EnemigoBase->GetEscudo() + EscudoExtra
        );

        GEngine->AddOnScreenDebugMessage(
            -1,
            5.f,
            FColor::Blue,
            TEXT("Escudo aplicado")
        );

        GetWorldTimerManager().SetTimer(
            TimerHandle_Escudo,
            this,
            &ADecoradorEscudo::RemoverEscudo,
            5.0f,
            false
        );
    }
}

void ADecoradorEscudo::RemoverEscudo()
{
    if (EnemigoBase)
    {
        EnemigoBase->SetEscudo(
            FMath::Max(
                0.0f,
                EnemigoBase->GetEscudo() - EscudoExtra
            )
        );

        GEngine->AddOnScreenDebugMessage(
            -1,
            5.f,
            FColor::Red,
            TEXT("Escudo removido")
        );
    }

    Destroy();
}
