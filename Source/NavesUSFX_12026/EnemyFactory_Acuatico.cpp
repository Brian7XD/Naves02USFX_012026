// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFactory_Acuatico.h"
#include "Enemigo_Acuatico.h"

// Sets default values
AEnemigo* AEnemyFactory_Acuatico::CrearEnemigo(
    FVector Posicion,
    FRotator Rotacion
)
{
    return GetWorld()->SpawnActor<AEnemigo_Acuatico>(
        AEnemigo_Acuatico::StaticClass(),
        Posicion,
        Rotacion
        );
}

