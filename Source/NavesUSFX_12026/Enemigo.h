// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Enemigo.generated.h"

class AControladorEnemigo;

UCLASS()
class NAVESUSFX_12026_API AEnemigo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemigo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void SetControlador(AControladorEnemigo* Ctrl);

    void Desaparecer();

protected:

    // Malla del enemigo
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Malla;

    // Dirección de movimiento
    FVector Direccion;

    // Velocidad
    UPROPERTY(EditAnywhere)
    float Velocidad;

    UPROPERTY(EditAnywhere)
    bool bPermitirMovimientoZ;

    AControladorEnemigo* Controlador;

    // Función para rebote
    UFUNCTION()
        void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
            UPrimitiveComponent* OtherComp, FVector NormalImpulse,
            const FHitResult& Hit);

};
