#include "Enemigo_Terrestre.h"
#include "UObject/ConstructorHelpers.h"

AEnemigo_Terrestre::AEnemigo_Terrestre()
{
	
	bPermitirMovimientoZ = false;
	Velocidad = 600.0f; 

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
		TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube")
	);

	if (MeshAsset.Succeeded())
	{
		Malla->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshProyectilAsset(
		TEXT("/Game/Geometry/Meshes/1M_Cube_Chamfer.1M_Cube_Chamfer")
	);

	if (MeshProyectilAsset.Succeeded())
	{
		MallaProyectil = MeshProyectilAsset.Object;
	}

	// 🔥 CONFIGURACIÓN DEL PROYECTIL
	VelocidadProyectil = 2000.f;
	DanioProyectil = 20.f;
}

void AEnemigo_Terrestre::ComportamientoParticular(float DeltaTime)
{
	Direccion.Z = 0;
	Direccion.Normalize();

	// Aplicamos el movimiento (el rebote de OnHit del padre se encargará de cambiar la Direccion)
	AddActorWorldOffset(Direccion * Velocidad * DeltaTime, true);
}


