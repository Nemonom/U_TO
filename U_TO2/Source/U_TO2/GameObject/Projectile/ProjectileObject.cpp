#include "ProjectileObject.h"
#include "../Player/PlayerObject.h"

AProjectileObject::AProjectileObject()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Objects/SM_Env_Breakables_GroupLg.SM_Env_Breakables_GroupLg"));
	if (Mesh.Succeeded())
		MeshComponent->SetStaticMesh(Mesh.Object);
	MeshComponent->SetCollisionProfileName(TEXT("Projectile"));


	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // 충돌 처리 활성화
	MeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic); // 충돌 그룹 설정
	//MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block); // 충돌 반응 설정
	

	SetRootComponent(MeshComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(MeshComponent);
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->MaxSpeed = 300.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	ProjectileMovementComponent->SetActive(true);

	InitialLifeSpan = 3.0f;
}

void AProjectileObject::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileObject::OnBeginOverlap);
}

void AProjectileObject::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(APlayerObject::StaticClass()))
	{
		Destroy();
	}
}

void AProjectileObject::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AProjectileObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

