#include "ControladorEnemigo.h"

// Tus clases
#include "Enemigo.h"
#include "Enemigo_Aereo.h"
#include "Enemigo_Terrestre.h"
#include "Enemigo_Acuatico.h"

AControladorEnemigo::AControladorEnemigo()
{
	EnemigosVivos = 0;
	bSegundaCuadrillaCreada = false;

	PrimaryActorTick.bCanEverTick = false;
}

void AControladorEnemigo::BeginPlay()
{
	Super::BeginPlay();

	CrearCuadrilla1();
}

void AControladorEnemigo::CrearCuadrilla1()
{
	FVector PosBase = GetActorLocation();

	AEnemigo* E1 = GetWorld()->SpawnActor<AEnemigo_Aereo>(PosBase + FVector(0, 0, 100), FRotator::ZeroRotator);
	AEnemigo* E2 = GetWorld()->SpawnActor<AEnemigo_Terrestre>(PosBase + FVector(200, 0, 0), FRotator::ZeroRotator);
	AEnemigo* E3 = GetWorld()->SpawnActor<AEnemigo_Acuatico>(PosBase + FVector(-200, 0, 0), FRotator::ZeroRotator);

	if (E1) E1->SetControlador(this);
	if (E2) E2->SetControlador(this);
	if (E3) E3->SetControlador(this);

	EnemigosVivos = 3;
}

void AControladorEnemigo::CrearCuadrilla2()
{
	FVector PosBase = GetActorLocation();

	AEnemigo* E1 = GetWorld()->SpawnActor<AEnemigo_Aereo>(PosBase + FVector(0, 200, 100), FRotator::ZeroRotator);
	AEnemigo* E2 = GetWorld()->SpawnActor<AEnemigo_Terrestre>(PosBase + FVector(200, 200, 0), FRotator::ZeroRotator);
	AEnemigo* E3 = GetWorld()->SpawnActor<AEnemigo_Acuatico>(PosBase + FVector(-200, 200, 0), FRotator::ZeroRotator);

	if (E1) E1->SetControlador(this);
	if (E2) E2->SetControlador(this);
	if (E3) E3->SetControlador(this);

	EnemigosVivos = 3;
}

void AControladorEnemigo::NotificarMuerte()
{
	EnemigosVivos--;

	// 🔥 CONDICIÓN DEL EJERCICIO
	if (EnemigosVivos <= 0 && !bSegundaCuadrillaCreada)
	{
		bSegundaCuadrillaCreada = true;

		// ⏱ Esperar antes de crear la siguiente cuadrilla
		GetWorld()->GetTimerManager().SetTimer(
			TimerSiguienteCuadrilla,
			this,
			&AControladorEnemigo::CrearCuadrilla2,
			3.0f,   // tiempo de espera (puedes cambiarlo)
			false
		);
	}
}

