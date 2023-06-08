#include "ProjectileObject.h"
#include "../Player/PlayerObject.h"
#include "../Enemy/EnemyObject.h"

AProjectileObject::AProjectileObject()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	
	FString MeshClassPath = "/Engine/BasicShapes/Cube";
	//FString MeshClassPath = "/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Objects/SM_Env_Breakables_GroupLg.SM_Env_Breakables_GroupLg";
	ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(*MeshClassPath);
	if (Mesh.Succeeded())
		MeshComponent->SetStaticMesh(Mesh.Object);
	MeshComponent->SetCollisionProfileName(TEXT("Projectile"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // 충돌 처리 활성화
	MeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic); // 충돌 그룹 설정
	//MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block); // 충돌 반응 설정
	

	SetRootComponent(MeshComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(MeshComponent);
	ProjectileMovementComponent->InitialSpeed = 300;
	ProjectileMovementComponent->MaxSpeed = 1000.0f;
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
	if (OtherActor)
	{
		if ((OtherActor->IsA(APlayerObject::StaticClass()) && AttackType == EAttackType::ENEMY)
			|| (OtherActor->IsA(AEnemyObject::StaticClass()) && AttackType == EAttackType::PLAYER))
		{
			FDamageEvent DamageEvent;
			OtherActor->TakeDamage(1.f, DamageEvent, GetInstigatorController(), this);

			Destroy();
		}
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

void AProjectileObject::Init(const EAttackType& InputAttackType)
{
	AttackType = InputAttackType;
}

void AProjectileObject::SetScale(const FVector& InputScale)
{
	MeshComponent->SetWorldScale3D(InputScale);
}

void AProjectileObject::SetSpeed(const float& InputSpeed)
{
	ProjectileMovementComponent->InitialSpeed = InputSpeed;
}