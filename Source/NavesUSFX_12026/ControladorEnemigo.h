#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ControladorEnemigo.generated.h"

class AEnemigo;

UCLASS()
class NAVESUSFX_12026_API AControladorEnemigo : public AActor
{
    GENERATED_BODY()

public:
    AControladorEnemigo();

protected:
    virtual void BeginPlay() override;

private:
    // Genera las 20 naves al inicio
    void SpawnNaves();

    // Funciones para el ciclo de comportamiento
    void OrdenarFormacion();
    void LiberarNaves();

public:
    void NotificarMuerte();

private:
    int32 EnemigosVivos;

    // Timers para las fases de 5 segundos
    FTimerHandle TimerFase;

    UPROPERTY()
        TArray<AEnemigo*> ContenedorNaves;
};
