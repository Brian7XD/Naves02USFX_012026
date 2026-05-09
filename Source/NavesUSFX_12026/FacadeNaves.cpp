// Fill out your copyright notice in the Description page of Project Settings.


#include "FacadeNaves.h"
#include "TimerManager.h"
#include "Engine/World.h"

AFacadeNaves::AFacadeNaves()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AFacadeNaves::IniciarAtaques()
{
	GetWorld()->GetTimerManager().SetTimer(
		TimerOleada1,
		this,
		&AFacadeNaves::Oleada1,
		3.0f,
		false
	);

	GetWorld()->GetTimerManager().SetTimer(
		TimerOleada2,
		this,
		&AFacadeNaves::Oleada2,
		10.0f,
		false
	);

	GetWorld()->GetTimerManager().SetTimer(
		TimerOleada3,
		this,
		&AFacadeNaves::Oleada3,
		20.0f,
		false
	);
}

void AFacadeNaves::Oleada1()
{
	LimpiarEnemigos();

	SpawnEscuadronExploracion(
		FVector(500, 0, 200)
	);
}

void AFacadeNaves::Oleada2()
{
	LimpiarEnemigos();

	SpawnAtaqueAnfibio(
		FVector(1000, 0, 100)
	);
}

void AFacadeNaves::Oleada3()
{
	LimpiarEnemigos();

	SpawnAsaltoTotal(
		FVector(1500, 0, 200)
	);
}

void AFacadeNaves::SpawnEnemigo(
	UClass* ClaseEnemigo,
	FVector Ubicacion
)
{
	if (GetWorld() && ClaseEnemigo)
	{
		AEnemigo* Nuevo =
			GetWorld()->SpawnActor<AEnemigo>(
				ClaseEnemigo,
				Ubicacion,
				FRotator::ZeroRotator
				);

		if (Nuevo)
		{
			EnemigosActuales.Add(Nuevo);
		}
	}
}

void AFacadeNaves::LimpiarEnemigos()
{
	for (AEnemigo* E : EnemigosActuales)
	{
		if (E)
		{
			E->Destroy();
		}
	}

	EnemigosActuales.Empty();
}

void AFacadeNaves::SpawnEscuadronExploracion(FVector Ubicacion)
{
	for (int i = 0; i < 3; i++)
	{
		FVector Offset(i * 200, i * 100, 0);

		SpawnEnemigo(
			AEnemigo_Aereo::StaticClass(),
			Ubicacion + Offset
		);
	}
}

void AFacadeNaves::SpawnAtaqueAnfibio(FVector Ubicacion)
{
	SpawnEnemigo(
		AEnemigo_Acuatico::StaticClass(),
		Ubicacion
	);

	SpawnEnemigo(
		AEnemigo_Terrestre::StaticClass(),
		Ubicacion + FVector(300, 0, 0)
	);
}

void AFacadeNaves::SpawnAsaltoTotal(FVector Ubicacion)
{
	SpawnEnemigo(
		AEnemigo_Aereo::StaticClass(),
		Ubicacion
	);

	SpawnEnemigo(
		AEnemigo_Terrestre::StaticClass(),
		Ubicacion + FVector(300, 0, 0)
	);

	SpawnEnemigo(
		AEnemigo_Acuatico::StaticClass(),
		Ubicacion + FVector(0, 0, 0)
	);
}


