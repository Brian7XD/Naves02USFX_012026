#include "Alienigena.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "NavesUSFX_12026Projectile.h"
#include "Engine/World.h"
#include "TimerManager.h"

// 🔹 CONSTRUCTOR
AAlienigena::AAlienigena()
{
	PrimaryActorTick.bCanEverTick = true;

	// 1. MALLA Y COMPONENTE (Mantener)
	Malla = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla"));
	RootComponent = Malla;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
		TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere")
	);

	if (MeshAsset.Succeeded())
	{
		Malla->SetStaticMesh(MeshAsset.Object);
	}

	// 2. CONFIGURACIÓN DE COLISIÓN (Modificar/Asegurar estas líneas)
	// Usamos BlockAllDynamic para que interactúe con otros objetos moviéndose
	Malla->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	// Esto es VITAL para que se ejecute la función OnHit
	Malla->SetNotifyRigidBodyCollision(true);
	Malla->OnComponentHit.AddDynamic(this, &AAlienigena::OnHit);

	Malla->SetEnableGravity(false); // Quita la gravedad para que no se pegue al suelo
	Malla->SetLinearDamping(0.0f);  // Quita el rozamiento del aire
	Malla->SetAngularDamping(0.0f); // Quita el rozamiento de giro

	// Bloqueamos los ejes para que no se caiga ni se incline
	if (Malla->GetBodyInstance())
	{
		Malla->GetBodyInstance()->bLockZTranslation = true;
		Malla->GetBodyInstance()->bLockXRotation = true;
		Malla->GetBodyInstance()->bLockYRotation = true;
	}

	// 3. VARIABLES DE MOVIMIENTO (Mantener)
	Velocidad = 600.f;
	Direccion = FVector(1, 0, 0);

	// 🔫 PROYECTIL DEFAULT
	ClaseProyectil = ANavesUSFX_12026Projectile::StaticClass();

	VelocidadProyectil = 800.f;
	DanioProyectil = 10.f;
}

// 🔹 BEGIN PLAY
void AAlienigena::BeginPlay()
{
	Super::BeginPlay();

	// 🔥 DISPARO AUTOMÁTICO
	GetWorldTimerManager().SetTimer(
		TimerDisparo,     
		this,
		&AAlienigena::Disparar,
		2.0f,
		true
	);
}

// 🔹 TICK (MOVIMIENTO)
void AAlienigena::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Direccion.IsNearlyZero())
	{
		Direccion = FVector(1, 0, 0);
	}

	FVector Desplazamiento = Direccion * Velocidad * DeltaTime;

	// Solo usamos el Sweep (true) para que se detenga al chocar.
	// El evento OnHit se encargará de cambiar la dirección.
	FHitResult Hit;
	AddActorWorldOffset(Desplazamiento, true, &Hit);
}

// 🔥 REBOTE
void AAlienigena::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	// 1. Invertir la dirección basándonos en la normal del choque
	Direccion = Direccion.MirrorByVector(Hit.Normal);

	// 2. Aplanamos y normalizamos para evitar velocidades extrañas
	Direccion.Z = 0;
	Direccion.Normalize();

	// 3. SEPARACIÓN FUERTE: Movemos al alienígena fuera de la colisión 
	// Usamos 10 unidades para asegurar que no toque la pared en el siguiente frame
	AddActorWorldOffset(Hit.Normal * 10.0f, false);
}

// 🔫 DISPARO
void AAlienigena::Disparar()
{
	if (!ClaseProyectil) return;

	FVector Posicion = GetActorLocation() + GetActorForwardVector() * 100;
	FRotator Rotacion = GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	ANavesUSFX_12026Projectile* Proyectil =
		GetWorld()->SpawnActor<ANavesUSFX_12026Projectile>(
			ClaseProyectil,
			Posicion,
			Rotacion,
			SpawnParams
			);

	if (Proyectil)
	{
		// 🔥 CORRECCIÓN AQUÍ: Añadimos 'false' y '0.0f' para los nuevos parámetros
		Proyectil->InicializarProyectil(
			MallaProyectil,
			VelocidadProyectil,
			DanioProyectil,
			false,  // bEsExplosivo
			0.0f    // RadioExplosion
		);
	}
}