#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h" 
#include "Enemigo.h"
#include "DecoradorEnemigo.generated.h"

UCLASS()
class NAVESUSFX_12026_API ADecoradorEnemigo : public AActor, public IEnemy
{
    GENERATED_BODY()

public:
    ADecoradorEnemigo();

protected:
    IEnemy* Enemigo;

    AEnemigo* EnemigoBase;

    virtual void BeginPlay() override;

public:
    virtual void SetEnemigo(AEnemigo* _Enemigo);

    virtual void Disparar() override;
    virtual void ComportamientoParticular(float DeltaTime) override;
    virtual void Die() override;
};