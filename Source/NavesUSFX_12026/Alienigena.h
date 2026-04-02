#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Alienigena.generated.h"

UCLASS()
class NAVESUSFX_12026_API AAlienigena : public APawn
{
	GENERATED_BODY()

public:
	AAlienigena();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// 🔹 COMPONENTE
protected:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Malla;

	// 🔹 MOVIMIENTO
protected:
	FVector Direccion;
	float Velocidad;

	// 🔹 PROYECTIL
protected:
	UPROPERTY(EditAnywhere, Category = "Disparo")
		TSubclassOf<class ANavesUSFX_12026Projectile> ClaseProyectil;

	UPROPERTY(EditAnywhere, Category = "Disparo")
		UStaticMesh* MallaProyectil;

	UPROPERTY(EditAnywhere, Category = "Disparo")
		float VelocidadProyectil;

	UPROPERTY(EditAnywhere, Category = "Disparo")
		float DanioProyectil;

protected:
	FTimerHandle TimerDisparo;

	// 🔹 FUNCIONES
protected:
	void Disparar();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, FVector NormalImpulse,
			const FHitResult& Hit);
};