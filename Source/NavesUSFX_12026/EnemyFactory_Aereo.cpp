// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFactory_Aereo.h"
#include "Enemigo_Aereo.h"

AEnemigo* AEnemyFactory_Aereo::CrearEnemigo(
    FVector Posicion,
    FRotator Rotacion
)
{
    return GetWorld()->SpawnActor<AEnemigo_Aereo>(
        AEnemigo_Aereo::StaticClass(),
        Posicion,
        Rotacion
        );
}