#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ControladorEnemigo.generated.h"

UCLASS()
class NAVESUSFX_12026_API AControladorEnemigo : public AActor
{
	GENERATED_BODY()

public:
	AControladorEnemigo();

protected:
	virtual void BeginPlay() override;

private:

	void CrearCuadrilla1();
	void CrearCuadrilla2();

public:

	void NotificarMuerte();

private:

	int EnemigosVivos;

	bool bSegundaCuadrillaCreada;

	FTimerHandle TimerSiguienteCuadrilla;
};
