// Fill out your copyright notice in the Description page of Project Settings.


#include "MuroBase_Mueve.h"

void AMuroBase_Mueve::EfectoEspecial(float DeltaTime) {
    // Usamos el tiempo del mundo y la función Seno para crear un movimiento oscilatorio
    float Tiempo = GetWorld()->GetTimeSeconds();
    float Desplazamiento = FMath::Sin(Tiempo * Velocidad) * Amplitud;

    // Suponiendo que se mueve en el eje Y
    FVector NuevaPosicion = GetActorLocation();
    NuevaPosicion.Y += (Desplazamiento * DeltaTime);

    SetActorLocation(NuevaPosicion);
}