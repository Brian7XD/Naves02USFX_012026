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

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshProyectilAsset(
        TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere")
    );

    if (MeshProyectilAsset.Succeeded())
    {
        MallaProyectil = MeshProyectilAsset.Object;
    }

    // Activar físicas de colisión
    Malla->SetSimulatePhysics(false);
    Malla->SetNotifyRigidBodyCollision(true);
    Malla->SetCollisionProfileName(TEXT("BlockAll"));
    Malla->SetGenerateOverlapEvents(true);

    // Evento de choque
    Malla->OnComponentHit.AddDynamic(this, &AEnemigo::OnHit);

    ProyectilClass = ANavesUSFX_12026Projectile::StaticClass();

    VelocidadProyectil = 800.f;
    DanioProyectil = 10.f;

}

void AEnemigo::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(
        TimerHandle_Disparo,
        this,
        &AEnemigo::Disparar,
        0.5f,   
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

    if (EstadoActual == EEstadoNave::Libre) {
        ComportamientoParticular(DeltaTime);
    }
    else if (EstadoActual == EEstadoNave::EnFormacion) {
        FVector NuevaPos = FMath::VInterpTo(GetActorLocation(), PosicionFormacion, DeltaTime, 2.0f);
        SetActorLocation(NuevaPos);
    }
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
        FVector SpawnLocation = GetActorLocation() + (GetActorForwardVector() * 200.0f) + FVector(0, 0, 50.0f);
        FRotator SpawnRotation = GetActorRotation();

        // Añadimos parámetros de Spawn
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this; // Definimos quién es el dueño

        ANavesUSFX_12026Projectile* Proyectil = GetWorld()->SpawnActor<ANavesUSFX_12026Projectile>(
            ProyectilClass,
            SpawnLocation,
            SpawnRotation,
            SpawnParams
            );

        if (Proyectil)
        {
            // ESTA LÍNEA ES CLAVE: La malla de la bala ignora al enemigo
            Proyectil->GetProjectileMesh()->IgnoreActorWhenMoving(this, true);

            Proyectil->InicializarProyectil(MallaProyectil, VelocidadProyectil, DanioProyectil);
        }
    }
}

void AEnemigo::ComportamientoParticular(float DeltaTime)
{
    // Este es el movimiento por defecto cuando están "Libres"
    // Si no es un enemigo especial (aéreo/terrestre), simplemente se mueve y rebota
    AddActorWorldOffset(Direccion * Velocidad * DeltaTime, true);
}
