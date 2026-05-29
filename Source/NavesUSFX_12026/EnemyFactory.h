
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyFactory.generated.h"

class AEnemigo;

UCLASS(Abstract)
class NAVESUSFX_12026_API AEnemyFactory : public AActor
{
    GENERATED_BODY()

public:
    virtual AEnemigo* CrearEnemigo(
        FVector Posicion,
        FRotator Rotacion
    );
};
