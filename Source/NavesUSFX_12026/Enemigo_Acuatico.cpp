#include "Enemigo_Acuatico.h"
#include "UObject/ConstructorHelpers.h"

AEnemigo_Acuatico::AEnemigo_Acuatico()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
		TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere")
	);

	if (MeshAsset.Succeeded())
	{
		Malla->SetStaticMesh(MeshAsset.Object);
	}
}

void AEnemigo_Acuatico::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Movimiento tipo "oleaje"
	Direccion.Y += FMath::Sin(GetWorld()->TimeSeconds) * 0.5f;

	Direccion.Normalize();
}