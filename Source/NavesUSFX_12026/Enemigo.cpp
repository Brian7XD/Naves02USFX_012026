#include "ControladorEnemigo.h"
#include "TimerManager.h"
#include "Enemigo.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AEnemigo::AEnemigo()
{
    PrimaryActorTick.bCanEverTick = true;
    Controlador = nullptr; // 🔥 IMPORTANTE

    bPermitirMovimientoZ = false;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
    // Crear malla
    Malla = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla"));
    RootComponent = Malla;

    if (MeshAsset.Succeeded())
    {
        Malla->SetStaticMesh(MeshAsset.Object);
    }

    // Activar físicas de colisión
    Malla->SetSimulatePhysics(false);
    Malla->SetNotifyRigidBodyCollision(true);
    Malla->SetCollisionProfileName(TEXT("BlockAll"));
    Malla->SetGenerateOverlapEvents(true);

    // Evento de choque
    Malla->OnComponentHit.AddDynamic(this, &AEnemigo::OnHit);

    ProyectilClass = ANavesUSFX_12026Projectile::StaticClass();

}

void AEnemigo::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(
        TimerHandle_Disparo,
        this,
        &AEnemigo::Disparar,
        0.5f,   // dispara cada 2 segundos
        true
    );

    Velocidad = 800.0f;
    // Dirección inicial aleatoria (sin Z)
    Direccion = FVector(
        FMath::FRandRange(-1.f, 1.f),
        FMath::FRandRange(-1.f, 1.f),
        0
    ).GetSafeNormal();

}

void AEnemigo::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Movimiento
    FVector NuevaPos = GetActorLocation() + (Direccion * Velocidad * DeltaTime);

    if (!bPermitirMovimientoZ)
    {
        NuevaPos.Z = GetActorLocation().Z;
    }

    SetActorLocation(NuevaPos, true);
}

void AEnemigo::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse,
    const FHitResult& Hit)
{
    // Rebote
    Direccion = Direccion - 2 * FVector::DotProduct(Direccion, Hit.Normal) * Hit.Normal;

    // 🔥 SACARLO DE LA PARED (CLAVE)
    FVector NuevaPos = GetActorLocation() + Hit.Normal * 5.0f;
    SetActorLocation(NuevaPos, false);

    // Mantener en plano si aplica
    Direccion.Z = 0;
    Direccion.Normalize();
}

void AEnemigo::Desaparecer()
{
    if (Controlador)
    {
        Controlador->NotificarMuerte();
    }

    Destroy();
}

void AEnemigo::SetControlador(AControladorEnemigo* Ctrl)
{
    Controlador = Ctrl;
}

void AEnemigo::Disparar()
{
    if (ProyectilClass)
    {
        FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
        FRotator SpawnRotation = GetActorRotation();

        GetWorld()->SpawnActor<ANavesUSFX_12026Projectile>(
            ProyectilClass,
            SpawnLocation,
            SpawnRotation
            );
    }
}


