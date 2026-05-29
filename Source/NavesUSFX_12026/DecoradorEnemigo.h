#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h" 
#include "Enemigo.h"
#include "DecoradorEnemigo.generated.h"

UCLASS()
class NAVESUSFX_12026_API ADecoradorEnemigo : public AEnemigo
{
    GENERATED_BODY()

public:
    ADecoradorEnemigo();

protected:

    AEnemigo* EnemigoBase;

    virtual void BeginPlay() override;

public:
    virtual void SetEnemigo(AEnemigo* _Enemigo);

    // Declaramos TODAS las funciones de la interfaz para asegurar que la clase NO sea abstracta
    virtual void Disparar() override;
    virtual void ComportamientoParticular(float DeltaTime) override;
    virtual void Die() override;

    virtual void RecibirDanio(float Danio) override;
    virtual float GetVida() const override;
    virtual float GetEscudo() const override;
    virtual float GetBlindaje() const override;
    virtual float GetVelocidad() const override;
};