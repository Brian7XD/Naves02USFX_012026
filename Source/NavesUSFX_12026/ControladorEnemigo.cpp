#include "ControladorEnemigo.h"
#include "Enemigo.h"
#include "Enemigo_Aereo.h"
#include "Enemigo_Terrestre.h"
#include "Enemigo_Acuatico.h"
#include "EnemyFactory.h"
#include "EnemyFactory_Aereo.h"
#include "EnemyFactory_Terrestre.h"
#include "EnemyFactory_Acuatico.h"
#include "DecoradorEscudo.h"
#include "DecoradorBlindaje.h"
#include "DecoradorVelocidad.h"
#include "Kismet/GameplayStatics.h" // Necesario para buscar al jugador

AControladorEnemigo::AControladorEnemigo()
{
    PrimaryActorTick.bCanEverTick = false;
    EnemigosVivos = 0;
}

void AControladorEnemigo::BeginPlay()
{
    Super::BeginPlay();

    // Crear factories
    Factories.Add(
        GetWorld()->SpawnActor<AEnemyFactory_Aereo>()
    );

    Factories.Add(
        GetWorld()->SpawnActor<AEnemyFactory_Terrestre>()
    );

    Factories.Add(
        GetWorld()->SpawnActor<AEnemyFactory_Acuatico>()
    );

    // Crear enemigos
    SpawnNaves();

    GetWorld()->GetTimerManager().SetTimer(
        TimerFase,
        this,
        &AControladorEnemigo::OrdenarFormacion,
        5.0f,
        false
    );
}

void AControladorEnemigo::SpawnNaves()
{
    FVector PosBase = GetActorLocation();

    for (int32 i = 0; i < 20; i++)
    {
        FVector SpawnOffset((i / 5) * 300.0f, (i % 5) * 300.0f, 100.0f);
        FVector FinalPos = PosBase + SpawnOffset;

        AEnemyFactory* Factory = Factories[i % 3];

        AEnemigo* NuevaNave = Factory->CrearEnemigo(FinalPos, FRotator::ZeroRotator);

        if (NuevaNave)
        {
            NuevaNave->SetControlador(this);

            AEnemigo* Base = NuevaNave;

            // 1. ESCUDO
            ADecoradorEscudo* DecoradorEscudo =
                GetWorld()->SpawnActor<ADecoradorEscudo>(ADecoradorEscudo::StaticClass(), FinalPos, FRotator::ZeroRotator);
            if (DecoradorEscudo)
            {
                DecoradorEscudo->SetEnemigo(Base);
                Base = DecoradorEscudo; // Ahora funciona porque DecoradorEscudo hereda de AEnemigo
            }

            // 2. BLINDAJE
            ADecoradorBlindaje* DecoradorBlindaje =
                GetWorld()->SpawnActor<ADecoradorBlindaje>(ADecoradorBlindaje::StaticClass(), FinalPos, FRotator::ZeroRotator);
            if (DecoradorBlindaje)
            {
                DecoradorBlindaje->SetEnemigo(Base);
                Base = DecoradorBlindaje;
            }

            // 3. VELOCIDAD
            ADecoradorVelocidad* DecoradorVelocidad =
                GetWorld()->SpawnActor<ADecoradorVelocidad>(ADecoradorVelocidad::StaticClass(), FinalPos, FRotator::ZeroRotator);
            if (DecoradorVelocidad)
            {
                DecoradorVelocidad->SetEnemigo(Base);
                Base = DecoradorVelocidad;
            }

            // Guardamos el contenedor final envuelto por los decoradores
            ContenedorNaves.Add(Base);
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

