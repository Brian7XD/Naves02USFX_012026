#include "Enemigo_Terrestre.h"
#include "UObject/ConstructorHelpers.h"

AEnemigo_Terrestre::AEnemigo_Terrestre()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
		TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube")
	);

	if (MeshAsset.Succeeded())
	{
		Malla->SetStaticMesh(MeshAsset.Object);
	}
}
