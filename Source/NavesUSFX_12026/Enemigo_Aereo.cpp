#include "Enemigo_Aereo.h"
#include "NavesUSFX_12026Projectile.h"
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
		TEXT("/Game/StarterContent/Shapes/Shape_Pipe.Shape_Pipe")
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

void AEnemigo_Aereo::Disparar()
{
    // 1. Verificamos que tengamos la clase del proyectil
    if (ProyectilClass)
    {
        // 2. Calculamos posición y rotación (igual que en el padre)
        FVector SpawnLocation = GetActorLocation() + (GetActorForwardVector() * 200.0f) + FVector(0, 0, 50.0f);
        FRotator SpawnRotation = GetActorRotation();

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;

        // 3. Spawneamos el proyectil
        ANavesUSFX_12026Projectile* Proyectil = GetWorld()->SpawnActor<ANavesUSFX_12026Projectile>(
            ProyectilClass,
            SpawnLocation,
            SpawnRotation,
            SpawnParams
            );

        if (Proyectil)
        {
            // 4. Ignorar colisión con el dueño
            Proyectil->GetProjectileMesh()->IgnoreActorWhenMoving(this, true);

            // 5. 🔥 POLIMORFISMO EN ACCIÓN:
            // Llamamos a InicializarProyectil pero pasando 'true' en el parámetro de explosión
            // y definimos un radio (ej. 500.0f)
            Proyectil->InicializarProyectil(MallaProyectil, VelocidadProyectil, DanioProyectil, true, 1000.0f);
        }
    }
}