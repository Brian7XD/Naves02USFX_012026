// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "NavesUSFX_12026Projectile.h"
#include "Enemigo.generated.h"

class AControladorEnemigo;

// Estados para el ejercicio de formación
UENUM(BlueprintType)
enum class EEstadoNave : uint8 {
    Libre,
    EnFormacion
};

UCLASS()
class NAVESUSFX_12026_API AEnemigo : public AActor
{
    GENERATED_BODY()

public:
    AEnemigo();

    // --- Funciones de Estado (NUEVO) ---
    void SetEstado(EEstadoNave NuevoEstado) { EstadoActual = NuevoEstado; }
    void SetPosicionFormacion(FVector NuevaPos) { PosicionFormacion = NuevaPos; }

    // --- Variables de Disparo (TUS ORIGINALES) ---
    UPROPERTY(EditAnywhere, Category = "Disparo")
        TSubclassOf<class ANavesUSFX_12026Projectile> ProyectilClass;

    UPROPERTY(EditAnywhere, Category = "Disparo")
        UStaticMesh* MallaProyectil;

    UPROPERTY(EditAnywhere, Category = "Disparo")
        float VelocidadProyectil;

    UPROPERTY(EditAnywhere, Category = "Disparo")
        float DanioProyectil;

    FTimerHandle TimerHandle_Disparo;

protected:
    virtual void BeginPlay() override;

    virtual void Disparar();

    // Función para que los hijos (Aéreo, Terrestre) pongan su movimiento aquí
    virtual void ComportamientoParticular(float DeltaTime);

    // --- Variables de Movimiento y Componentes (TUS ORIGINALES + NUEVOS) ---
    UPROPERTY(VisibleAnywhere)
        UStaticMeshComponent* Malla;

    FVector Direccion;

    UPROPERTY(EditAnywhere)
        float Velocidad;

    UPROPERTY(EditAnywhere)
        bool bPermitirMovimientoZ;

    AControladorEnemigo* Controlador;
    EEstadoNave EstadoActual = EEstadoNave::Libre;
    FVector PosicionFormacion;

public:
    virtual void Tick(float DeltaTime) override;
    void SetControlador(AControladorEnemigo* Ctrl);
    void Desaparecer();

    UFUNCTION()
        void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
            UPrimitiveComponent* OtherComp, FVector NormalImpulse,
            const FHitResult& Hit);
};
