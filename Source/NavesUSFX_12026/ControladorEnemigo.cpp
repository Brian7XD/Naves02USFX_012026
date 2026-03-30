#include "ControladorEnemigo.h"
#include "Enemigo.h"
#include "Enemigo_Aereo.h"
#include "Enemigo_Terrestre.h"
#include "Enemigo_Acuatico.h"
#include "Kismet/GameplayStatics.h" // Necesario para buscar al jugador

AControladorEnemigo::AControladorEnemigo()
{
    PrimaryActorTick.bCanEverTick = false;
    EnemigosVivos = 0;
}

void AControladorEnemigo::BeginPlay()
{
    Super::BeginPlay();

    // 1. Iniciamos el juego creando las naves
    SpawnNaves();

    // 2. Programamos: A los 5 segundos, que se formen
    GetWorld()->GetTimerManager().SetTimer(TimerFase, this, &AControladorEnemigo::OrdenarFormacion, 5.0f, false);
}

void AControladorEnemigo::SpawnNaves()
{
    FVector PosBase = GetActorLocation();

    for (int32 i = 0; i < 20; i++)
    {
        // Distribución simple para que no choquen al nacer
        FVector SpawnOffset((i / 5) * 300.0f, (i % 5) * 300.0f, 100.0f);
        FVector FinalPos = PosBase + SpawnOffset;

        AEnemigo* NuevaNave = nullptr;

        // Alternamos tipos para variedad
        if (i % 3 == 0) NuevaNave = GetWorld()->SpawnActor<AEnemigo_Aereo>(AEnemigo_Aereo::StaticClass(), FinalPos, FRotator::ZeroRotator);
        else if (i % 3 == 1) NuevaNave = GetWorld()->SpawnActor<AEnemigo_Terrestre>(AEnemigo_Terrestre::StaticClass(), FinalPos, FRotator::ZeroRotator);
        else NuevaNave = GetWorld()->SpawnActor<AEnemigo_Acuatico>(AEnemigo_Acuatico::StaticClass(), FinalPos, FRotator::ZeroRotator);

        if (NuevaNave)
        {
            NuevaNave->SetControlador(this);
            ContenedorNaves.Add(NuevaNave);
        }
    }
    EnemigosVivos = ContenedorNaves.Num();
}

void AControladorEnemigo::OrdenarFormacion()
{
    // Buscamos al Pawn del jugador
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn) return;

    // Calculamos un punto 12 metros al frente del jugador
    FVector PuntoFrente = PlayerPawn->GetActorLocation() + (PlayerPawn->GetActorForwardVector() * 1200.0f);

    for (int32 i = 0; i < ContenedorNaves.Num(); i++)
    {
        if (ContenedorNaves[i])
        {
            // Creamos una cuadrilla: 5 columnas x 4 filas
            FVector OffsetFormacion((i / 5) * 250.0f, (i % 5) * 250.0f, 0.0f);

            ContenedorNaves[i]->SetPosicionFormacion(PuntoFrente + OffsetFormacion);
            ContenedorNaves[i]->SetEstado(EEstadoNave::EnFormacion);
        }
    }

    // Programamos: A los 5 segundos de estar en formación, volver a ser libres
    GetWorld()->GetTimerManager().SetTimer(TimerFase, this, &AControladorEnemigo::LiberarNaves, 5.0f, false);
}

void AControladorEnemigo::LiberarNaves()
{
    for (AEnemigo* Nave : ContenedorNaves)
    {
        if (Nave)
        {
            Nave->SetEstado(EEstadoNave::Libre);
        }
    }
}

void AControladorEnemigo::NotificarMuerte()
{
    EnemigosVivos--;
}

