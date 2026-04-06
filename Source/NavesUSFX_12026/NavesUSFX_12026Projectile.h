// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavesUSFX_12026Projectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS(config = Game)
class ANavesUSFX_12026Projectile : public AActor
{
    GENERATED_BODY()

        /** Componente de malla del proyectil */
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
        UStaticMeshComponent* ProjectileMesh;

    /** Componente de movimiento del proyectil */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
        UProjectileMovementComponent* ProjectileMovement;

    UPROPERTY(EditAnywhere, Category = "Config")
        UStaticMesh* MallaConfigurable;

    UPROPERTY(EditAnywhere, Category = "Config")
        float Velocidad;

    UPROPERTY(EditAnywhere, Category = "Config")
        float Danio;

    UPROPERTY(EditAnywhere, Category = "Efectos")
        class UParticleSystem* EfectoExplosion;

    // --- VARIABLES PARA POLIMORFISMO DE EXPLOSIÓN ---
    UPROPERTY(EditAnywhere, Category = "Config")
        bool bEsExplosivo = false;

    UPROPERTY(EditAnywhere, Category = "Config")
        float RadioExplosion = 300.0f;

public:
    ANavesUSFX_12026Projectile();

    /** * Función de inicialización extendida para soportar diferentes tipos de proyectiles.
     * Ahora acepta parámetros de explosión para permitir el comportamiento polimórfico.
     */
    void InicializarProyectil(UStaticMesh* NuevaMalla, float NuevaVelocidad, float NuevoDanio, bool bExplosivo, float NuevoRadio);

    /** Función para manejar la colisión del proyectil */
    UFUNCTION()
        void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    /** Retorna el ProjectileMesh subobject **/
    FORCEINLINE UStaticMeshComponent* GetProjectileMesh() const { return ProjectileMesh; }
    /** Retorna el ProjectileMovement subobject **/
    FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

protected:
    virtual void BeginPlay() override;
};
