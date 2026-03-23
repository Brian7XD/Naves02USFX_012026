#include "Enemigo_Aereo.h"
#include "UObject/ConstructorHelpers.h"

AEnemigo_Aereo::AEnemigo_Aereo()
{
	bPermitirMovimientoZ = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
		TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone")
	);

	if (MeshAsset.Succeeded())
	{
		Malla->SetStaticMesh(MeshAsset.Object);
	}
}

void AEnemigo_Aereo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Direccion.Z = FMath::Sin(GetWorld()->TimeSeconds) * 0.3f;

	Direccion.Normalize();
}