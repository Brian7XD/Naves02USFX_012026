// Copyright Epic Games, Inc. All Rights Reserve

#include "NavesUSFX_12026Projectile.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"

ANavesUSFX_12026Projectile::ANavesUSFX_12026Projectile() 
{
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	RootComponent = ProjectileMesh;

	ProjectileMesh->SetWorldScale3D(FVector(1.0f));

	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ANavesUSFX_12026Projectile::OnHit);		// set up a notification for when this component hits something
	
	Velocidad = 800.f;
	Danio = 10.f;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = Velocidad;
	ProjectileMovement->MaxSpeed = Velocidad;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

	// Cargar el efecto de explosión del Starter Content
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));

	if (ParticleAsset.Succeeded())
	{
		EfectoExplosion = ParticleAsset.Object;
	}

}

void ANavesUSFX_12026Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		// --- AÑADE ESTO PARA MOVER BLOQUES ---
		if (OtherComp->IsSimulatingPhysics())
		{
			// Aplicar un impulso en el punto de impacto
			// Puedes multiplicar Hit.ImpactNormal por un valor negativo para empujar
			OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
		}

		if (bEsExplosivo)
		{
			UGameplayStatics::ApplyRadialDamage(this, Danio, GetActorLocation(), RadioExplosion, UDamageType::StaticClass(), TArray<AActor*>(), this);
			if (EfectoExplosion)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EfectoExplosion, GetActorLocation(), FRotator::ZeroRotator, FVector(2.0f));
			}
		}
	}
	Destroy();
}

void ANavesUSFX_12026Projectile::BeginPlay()
{
	Super::BeginPlay();

	if (MallaConfigurable)
	{
		ProjectileMesh->SetStaticMesh(MallaConfigurable);
	}

	// Aplicar velocidad
	if (ProjectileMovement)
	{
		ProjectileMovement->InitialSpeed = Velocidad;
		ProjectileMovement->MaxSpeed = Velocidad;
	}
}
void ANavesUSFX_12026Projectile::InicializarProyectil(UStaticMesh* NuevaMalla, float NuevaVelocidad, float NuevoDanio, bool bExplosivo, float NuevoRadio)
{
	// 1. Cambiar la malla visual
	if (NuevaMalla)
	{
		ProjectileMesh->SetStaticMesh(NuevaMalla);
	}

	// 2. Asignar stats básicos
	Velocidad = NuevaVelocidad;
	Danio = NuevoDanio;

	// 3. Asignar stats de polimorfismo (NUEVO)
	bEsExplosivo = bExplosivo;
	RadioExplosion = NuevoRadio;

	// 4. Configurar el movimiento físico
	if (ProjectileMovement)
	{
		ProjectileMovement->MaxSpeed = Velocidad;
		ProjectileMovement->InitialSpeed = Velocidad;

		// Actualiza el vector de movimiento real con la nueva velocidad
		ProjectileMovement->Velocity = GetActorForwardVector() * Velocidad;
	}
}