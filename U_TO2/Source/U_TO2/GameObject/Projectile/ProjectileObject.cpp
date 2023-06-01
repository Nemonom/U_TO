#include "ProjectileObject.h"

// Sets default values
AProjectileObject::AProjectileObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Objects/SM_Env_Breakables_GroupLg.SM_Env_Breakables_GroupLg"));
	if (Mesh.Succeeded())
		MeshComponent->SetStaticMesh(Mesh.Object);
	MeshComponent->SetCollisionProfileName(TEXT("Projectile"));
	SetRootComponent(MeshComponent);

	/*CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->SetupAttachment(MeshComponent);*/

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(MeshComponent);
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->MaxSpeed = 300.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->SetActive(true);
}

void AProjectileObject::BeginPlay()
{
	Super::BeginPlay();

}

void AProjectileObject::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AProjectileObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

