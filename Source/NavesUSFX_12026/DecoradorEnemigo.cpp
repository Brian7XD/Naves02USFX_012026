// Fill out your copyright notice in the Description page of Project Settings.

#include "DecoradorEnemigo.h"
#include "Enemigo.h" 

ADecoradorEnemigo::ADecoradorEnemigo()
{
    PrimaryActorTick.bCanEverTick = true;
    EnemigoBase = nullptr;
}

void ADecoradorEnemigo::BeginPlay()
{
    Super::BeginPlay();
}

void ADecoradorEnemigo::SetEnemigo(AEnemigo* _Enemigo)
{
    EnemigoBase = _Enemigo;
}

// --- REENVÍO DE MÉTODOS AL ENEMIGO BASE ---

void ADecoradorEnemigo::Disparar()
{
    if (EnemigoBase) EnemigoBase->Disparar();
}

void ADecoradorEnemigo::ComportamientoParticular(float DeltaTime)
{
    if (EnemigoBase) EnemigoBase->ComportamientoParticular(DeltaTime);
}

void ADecoradorEnemigo::Die()
{
    if (EnemigoBase) EnemigoBase->Die();
}

void ADecoradorEnemigo::RecibirDanio(float Danio)
{
    if (EnemigoBase) EnemigoBase->RecibirDanio(Danio);
}

float ADecoradorEnemigo::GetVida() const
{
    return EnemigoBase ? EnemigoBase->GetVida() : 0.0f;
}

float ADecoradorEnemigo::GetEscudo() const
{
    return EnemigoBase ? EnemigoBase->GetEscudo() : 0.0f;
}

float ADecoradorEnemigo::GetBlindaje() const
{
    return EnemigoBase ? EnemigoBase->GetBlindaje() : 0.0f;
}

float ADecoradorEnemigo::GetVelocidad() const
{
    return EnemigoBase ? EnemigoBase->GetVelocidad() : 0.0f;
}

