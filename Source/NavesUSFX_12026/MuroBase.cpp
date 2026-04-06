// Fill out your copyright notice in the Description page of Project Settings.

// MuroBase.cpp
#include "MuroBase.h"
#include "UObject/ConstructorHelpers.h"

// Constructor
AMuroBase::AMuroBase()
{
    // Permitir que el Tick se ejecute en cada frame
    PrimaryActorTick.bCanEverTick = true;

    // Creamos el componente de malla y lo establecemos como raíz
    MallaMuro = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaMuro"));
    RootComponent = MallaMuro;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));

    if (MeshAsset.Succeeded())
    {
        // Si el motor encontró el archivo, se lo asignamos al componente
        MallaMuro->SetStaticMesh(MeshAsset.Object);
        MallaMuro->SetWorldScale3D(FVector(1.0f));
    }
    else
    {
        // Mensaje de error en el log si no encuentra la malla
        UE_LOG(LogTemp, Error, TEXT("MuroBase: No se pudo encontrar la malla en la ruta especificada."));
    }
}

void AMuroBase::BeginPlay()
{
    Super::BeginPlay();
}

// Implementación base (puede estar vacía o tener un comportamiento por defecto)
void AMuroBase::EfectoEspecial(float DeltaTime)
{
    // Los muros normales no hacen nada especial
}

void AMuroBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Gracias al polimorfismo, si este objeto es una clase hija, 
    // ejecutará la versión sobrescrita de esta función.
    EfectoEspecial(DeltaTime);
}

