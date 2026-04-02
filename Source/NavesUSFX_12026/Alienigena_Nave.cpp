// Fill out your copyright notice in the Description page of Project Settings.


#include "Alienigena_Nave.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

AAlienigena_Nave::AAlienigena_Nave()
{
    TiempoOscilacion = 0.f;

    // 1. Malla de la Nave (Esfera)
    static ConstructorHelpers::FObjectFinder<UStaticMesh> NaveMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
    if (NaveMesh.Succeeded())
    {
        Malla->SetStaticMesh(NaveMesh.Object);
    }

    // 2. Malla del Proyectil (Cápsula)
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ProyectilMesh(TEXT("/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule"));
    if (ProyectilMesh.Succeeded())
    {
        MallaProyectil = ProyectilMesh.Object;
    }

    // 3. Estadísticas
    Velocidad = 750.f;
    VelocidadProyectil = 1400.f;
    DanioProyectil = 10.f;
}

void AAlienigena_Nave::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    TiempoOscilacion += DeltaTime;

    // Movimiento ondulatorio rápido (Frecuencia: 6, Amplitud: 25)
    float OffsetLateral = FMath::Sin(TiempoOscilacion * 6.0f) * 25.0f;
    FVector VectorLateral = FVector(-Direccion.Y, Direccion.X, 0);

    FVector Desplazamiento = (Direccion * Velocidad * DeltaTime) + (VectorLateral * OffsetLateral * DeltaTime);

    FHitResult Hit;
    AddActorWorldOffset(Desplazamiento, true, &Hit);
}
