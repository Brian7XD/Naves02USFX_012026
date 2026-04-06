// Fill out your copyright notice in the Description page of Project Settings.
// MuroBase.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MuroBase.generated.h"

UCLASS()
class NAVESUSFX_12026_API AMuroBase : public AActor
{
    GENERATED_BODY()

public:
    // Establece valores predeterminados para las propiedades de este actor
    AMuroBase();

protected:
    // Llamado cuando comienza el juego o cuando se genera el actor
    virtual void BeginPlay() override;

    // Componente de malla estática para la visualización y colisión del muro
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Muro")
        UStaticMeshComponent* MallaMuro;

    /** * Función virtual que define el comportamiento único del muro.
     * Se marca como virtual para que las clases hijas puedan sobrescribirla (Polimorfismo).
     */
    virtual void EfectoEspecial(float DeltaTime);

public:
    // Llamado en cada frame
    virtual void Tick(float DeltaTime) override;
};
