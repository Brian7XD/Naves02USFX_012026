#include "Crear_Laberinto.h"
#include "Engine/World.h"
#include "Engine/Engine.h" // <--- NUEVO: Necesario para mensajes en pantalla

ACrear_Laberinto::ACrear_Laberinto()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ACrear_Laberinto::BeginPlay()
{
    Super::BeginPlay();

    // MENSAJE DE PRUEBA: Si ves esto en pantalla al dar Play, el código funciona
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Generando Laberinto..."));
    }

    ConstruirLaberinto();
}

void ACrear_Laberinto::ConstruirLaberinto()
{
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    // 1. Limpiamos el contenedor antes de empezar (por seguridad)
    MurosGenerados.Empty();

    for (int32 i = 0; i < Filas; i++)
    {
        for (int32 j = 0; j < Columnas; j++)
        {
            FVector Ubicacion = GetActorLocation() + FVector(i * Espaciado, j * Espaciado, 200.0f);

            UClass* ClaseParaSpawnear = nullptr;
            int32 Seleccion = FMath::RandRange(0, 5);

            switch (Seleccion)
            {
            case 1: ClaseParaSpawnear = AMuroBase_Mueve::StaticClass(); break;
            case 2: ClaseParaSpawnear = AMuroBase_Desaparece::StaticClass(); break;
            case 3: ClaseParaSpawnear = AMuroBase_Divide::StaticClass(); break;
            default: ClaseParaSpawnear = AMuroBase::StaticClass(); break;
            }

            if (ClaseParaSpawnear)
            {
                // 2. Guardamos el resultado del Spawn en una variable temporal
                AActor* NuevoMuro = GetWorld()->SpawnActor<AActor>(ClaseParaSpawnear, Ubicacion, FRotator::ZeroRotator, SpawnParams);

                // 3. Si el muro se creó correctamente, lo añadimos al TArray
                if (NuevoMuro)
                {
                    MurosGenerados.Add(NuevoMuro);
                }
            }
        }
    }

    // Opcional: Un mensaje para confirmar en el log cuántos muros guardaste
    UE_LOG(LogTemp, Warning, TEXT("Laberinto creado con %d muros guardados en el contenedor."), MurosGenerados.Num());
}
