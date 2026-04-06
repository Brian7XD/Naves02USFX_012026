// Fill out your copyright notice in the Description page of Project Settings.


#include "MuroBase_Desaparece.h"

void AMuroBase_Desaparece::EfectoEspecial(float DeltaTime) {
    TiempoAcumulado += DeltaTime;

    if (TiempoAcumulado >= Intervalo) {
        // Invertimos la visibilidad actual
        bool bNuevaVisibilidad = !IsHidden();

        SetActorHiddenInGame(bNuevaVisibilidad);
        SetActorEnableCollision(!bNuevaVisibilidad); // Si está oculto, no tiene colisión

        TiempoAcumulado = 0.0f; // Reiniciamos el contador
    }
}