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

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshProyectilAsset(
		TEXT("/ Game / StarterContent / Shapes / Shape_Pipe.Shape_Pipe")
	);

	if (MeshProyectilAsset.Succeeded())
	{
		MallaProyectil = MeshProyectilAsset.Object;
	}

	// 🔥 CONFIGURACIÓN DEL PROYECTIL
	VelocidadProyectil = 2000.f;
	DanioProyectil = 20.f;
}

void AEnemigo_Aereo::ComportamientoParticular(float DeltaTime)
{
	if (bPermitirMovimientoZ)
	{
		Direccion.Z = FMath::Sin(GetWorld()->GetTimeSeconds()) * 0.2f;
	}

	Direccion.Normalize();

	AddActorWorldOffset(Direccion * Velocidad * DeltaTime, true);
}