#include "Enemigo_Acuatico.h"
#include "UObject/ConstructorHelpers.h"

AEnemigo_Acuatico::AEnemigo_Acuatico()
{
	Velocidad = 550.0f;
	bPermitirMovimientoZ = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
		TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere")
	);

	if (MeshAsset.Succeeded())
	{
		Malla->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshProyectilAsset(
		TEXT("/Game/StarterContent/Shapes/Shape_Torus.Shape_Torus")
	);

	if (MeshProyectilAsset.Succeeded())
	{
		MallaProyectil = MeshProyectilAsset.Object;
	}

	// 🔥 CONFIGURACIÓN DEL PROYECTIL
	VelocidadProyectil = 2000.f;
	DanioProyectil = 20.f;
}

void AEnemigo_Acuatico::ComportamientoParticular(float DeltaTime)
{
	// Movimiento tipo "oleaje" en el eje Y
	Direccion.Y += FMath::Sin(GetWorld()->TimeSeconds) * 0.5f;

	Direccion.Normalize();

	// Aplicamos el movimiento final
	AddActorWorldOffset(Direccion * Velocidad * DeltaTime, true);
}