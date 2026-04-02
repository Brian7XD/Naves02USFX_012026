
#include "Engine/StaticMeshActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Crear_Camino.h"
#include "Engine/World.h"

ACrear_Camino::ACrear_Camino()
{
	PrimaryActorTick.bCanEverTick = false;

	// 🔥 Cargar malla de cubo
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Malla(
		TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube")
	);

	if (Malla.Succeeded())
	{
		MallaBloque = Malla.Object;
	}
}

void ACrear_Camino::BeginPlay()
{
	Super::BeginPlay();

	// 🔹 Generar bloques en línea
	for (int i = 0; i < 10; i++)
	{
		FVector Posicion = FVector(i * 200, 0, 100);

		AStaticMeshActor* Bloque = GetWorld()->SpawnActor<AStaticMeshActor>(Posicion, FRotator::ZeroRotator);

		if (Bloque && MallaBloque)
		{
			Bloque->GetStaticMeshComponent()->SetStaticMesh(MallaBloque);

			ListaBloques.Insertar(Bloque);
		}
	}

	auto nodo = ListaBloques.GetCabeza();

	while (nodo != nullptr)
	{
		AActor* bloque = nodo->dato;

		if (bloque)
		{
			UE_LOG(LogTemp, Warning, TEXT("Bloque en posicion: %s"),
				*bloque->GetActorLocation().ToString());
		}

		nodo = nodo->siguiente;
	}
}


