// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MuroBase.h"
#include "MuroBase_Mueve.h"
#include "MuroBase_Divide.h"
#include "MuroBase_Desaparece.h"
#include "Crear_Laberinto.generated.h"

UCLASS()
class NAVESUSFX_12026_API ACrear_Laberinto : public AActor
{
    GENERATED_BODY()

public:
    ACrear_Laberinto();

protected:
    virtual void BeginPlay() override;

private:
    // Configuración del tamaño del laberinto
    int32 Filas = 20;
    int32 Columnas = 20;
    float Espaciado = 200.0f;

    TArray<AActor*> MurosGenerados;

    void ConstruirLaberinto();
};
