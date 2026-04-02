// Fill out your copyright notice in the Description page of Project Settings.


#include "Alienigena_Flota.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

AAlienigena_Flota::AAlienigena_Flota()
{
    TiempoOscilacion = 0.f;

    // 1. Malla de la Flota (Cono)
    static ConstructorHelpers::FObjectFinder<UStaticMesh> FlotaMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone"));
    if (FlotaMesh.Succeeded())
    {
        Malla->SetStaticMesh(FlotaMesh.Object);
    }

    // 2. Malla del Proyectil (Cilindro)
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ProyectilMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
    if (ProyectilMesh.Succeeded())
    {
        MallaProyectil = ProyectilMesh.Object;
    }

    // 3. Estadísticas y Escala
    Velocidad = 300.f;
    VelocidadProyectil = 600.f;
    DanioProyectil = 40.f;
    SetActorScale3D(FVector(1.8f, 1.8f, 1.8f)); // Nave más imponente
}

void AAlienigena_Flota::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    TiempoOscilacion += DeltaTime;

    // Movimiento ondulatorio lento y amplio (Frecuencia: 2.5, Amplitud: 50)
    float OffsetLateral = FMath::Cos(TiempoOscilacion * 2.5f) * 50.0f;
    FVector VectorLateral = FVector(-Direccion.Y, Direccion.X, 0);

    FVector Desplazamiento = (Direccion * Velocidad * DeltaTime) + (VectorLateral * OffsetLateral * DeltaTime);

    FHitResult Hit;
    AddActorWorldOffset(Desplazamiento, true, &Hit);
}