// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemigo.h"
#include "Enemigo_Acuatico.h"
#include "Enemigo_Aereo.h"
#include "Enemigo_Terrestre.h"
#include "FacadeNaves.generated.h"

UCLASS()
class NAVESUSFX_12026_API AFacadeNaves : public AActor
{
	GENERATED_BODY()

public:
	AFacadeNaves();

	void IniciarAtaques();

private:

	void Oleada1();
	void Oleada2();
	void Oleada3();

	void SpawnEnemigo(UClass* ClaseEnemigo, FVector Ubicacion);

	void SpawnEscuadronExploracion(FVector Ubicacion);
	void SpawnAtaqueAnfibio(FVector Ubicacion);
	void SpawnAsaltoTotal(FVector Ubicacion);

	void LimpiarEnemigos();

private:

	UPROPERTY()
		TArray<AEnemigo*> EnemigosActuales;

	FTimerHandle TimerOleada1;
	FTimerHandle TimerOleada2;
	FTimerHandle TimerOleada3;
};
