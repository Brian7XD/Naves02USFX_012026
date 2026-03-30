// Copyright Epic Games, Inc. All Rights Reserve

#include "NavesUSFX_12026Projectile.h"
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

}

void ANavesUSFX_12026Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
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
void ANavesUSFX_12026Projectile::InicializarProyectil(UStaticMesh* NuevaMalla, float NuevaVelocidad, float NuevoDanio)
{
	if (NuevaMalla)
	{
		ProjectileMesh->SetStaticMesh(NuevaMalla);
	}

	Velocidad = NuevaVelocidad;
	Danio = NuevoDanio;

	if (ProjectileMovement)
	{
		// No basta con setear InitialSpeed, hay que setear la velocidad actual
		ProjectileMovement->MaxSpeed = Velocidad;
		ProjectileMovement->InitialSpeed = Velocidad;

		// ESTA LÍNEA ES VITAL: Actualiza el vector de movimiento real
		ProjectileMovement->Velocity = GetActorForwardVector() * Velocidad;
	}
}