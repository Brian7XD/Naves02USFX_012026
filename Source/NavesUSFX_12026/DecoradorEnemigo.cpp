// Fill out your copyright notice in the Description page of Project Settings.

#include "DecoradorEnemigo.h"
#include "Enemigo.h" 

ADecoradorEnemigo::ADecoradorEnemigo()
{
    PrimaryActorTick.bCanEverTick = true;
    Enemigo = nullptr;
}

void ADecoradorEnemigo::BeginPlay()
{
    Super::BeginPlay();

}

void ADecoradorEnemigo::SetEnemigo(AEnemigo* _Enemigo)
{
    EnemigoBase = _Enemigo;
    Enemigo = Cast<IEnemy>(_Enemigo);
}

void ADecoradorEnemigo::Disparar()
{
    if (Enemigo)
    {
        Enemigo->Disparar();
    }
}

void ADecoradorEnemigo::ComportamientoParticular(float DeltaTime)
{
    if (Enemigo)
    {
        Enemigo->ComportamientoParticular(DeltaTime);
    }
}

void ADecoradorEnemigo::Die()
{
    if (Enemigo)
    {
        Enemigo->Die();
    }
}


