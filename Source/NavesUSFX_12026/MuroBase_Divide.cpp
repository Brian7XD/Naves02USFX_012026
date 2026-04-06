// Fill out your copyright notice in the Description page of Project Settings.


#include "MuroBase_Divide.h"

void AMuroBase_Divide::EfectoEspecial(float DeltaTime) {
    if (bYaSeDividio) return;

    Cronometro += DeltaTime;
    if (Cronometro >= 5.0f) { // Se divide a los 5 segundos
        FVector NuevaUbicacion = GetActorLocation() + (GetActorForwardVector() * 200.0f);

        // Spawneamos un nuevo muro (puede ser un MuroBase normal)
        if (ClaseAGenerar) {
            GetWorld()->SpawnActor<AMuroBase>(ClaseAGenerar, NuevaUbicacion, GetActorRotation());
        }

        bYaSeDividio = true; // Evitamos que siga spawneando infinitamente
    }
}