#include "Enemigo.h"
#include "ControladorEnemigo.h"
#include "TimerManager.h"
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

    Vida = 100.0f;
    Blindaje = 0.0f;
    Escudo = 0.0f;
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

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;

        ANavesUSFX_12026Projectile* Proyectil = GetWorld()->SpawnActor<ANavesUSFX_12026Projectile>(
            ProyectilClass,
            SpawnLocation,
            SpawnRotation,
            SpawnParams
            );

        if (Proyectil)
        {
            Proyectil->GetProjectileMesh()->IgnoreActorWhenMoving(this, true);
            Proyectil->InicializarProyectil(MallaProyectil, VelocidadProyectil, DanioProyectil, false, 0.0f);
        }
    }
}

void AEnemigo::ComportamientoParticular(float DeltaTime)
{
    AddActorWorldOffset(Direccion * Velocidad * DeltaTime, true);
}

void AEnemigo::Die()
{
    Desaparecer();
}

void AEnemigo::RecibirDanio(float Danio)
{
    Danio -= Blindaje;

    Danio = FMath::Max(0.0f, Danio);

    if (Escudo > 0)
    {
        if (Escudo >= Danio)
        {
            Escudo -= Danio;
            Danio = 0;
        }
        else
        {
            Danio -= Escudo;
            Escudo = 0;
        }
    }

    Vida -= Danio;

    UE_LOG(LogTemp, Warning,
        TEXT("Vida: %f | Escudo: %f"),
        Vida,
        Escudo
    );

    if (Vida <= 0)
    {
        Die();
    }
}

float AEnemigo::GetVida() const
{
    return Vida;
}

void AEnemigo::SetVida(float NuevaVida)
{
    Vida = NuevaVida;
}

float AEnemigo::GetBlindaje() const
{
    return Blindaje;
}

void AEnemigo::SetBlindaje(float NuevoBlindaje)
{
    Blindaje = NuevoBlindaje;
}

float AEnemigo::GetEscudo() const
{
    return Escudo;
}

void AEnemigo::SetEscudo(float NuevoEscudo)
{
    Escudo = NuevoEscudo;
}

float AEnemigo::GetVelocidad() const
{
    return Velocidad;
}

void AEnemigo::SetVelocidad(float NuevaVelocidad)
{
    Velocidad = NuevaVelocidad;
}