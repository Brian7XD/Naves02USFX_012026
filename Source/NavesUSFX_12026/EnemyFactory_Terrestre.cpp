// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFactory_Terrestre.h"
#include "Enemigo_Terrestre.h"

AEnemigo* AEnemyFactory_Terrestre::CrearEnemigo(
    FVector Posicion,
    FRotator Rotacion
)
{
    return GetWorld()->SpawnActor<AEnemigo_Terrestre>(
        AEnemigo_Terrestre::StaticClass(),
        Posicion,
        Rotacion
        );
}
