#include "BaseGameObject.h"
#include "CharacterStatComponent.h"
#include "Components/WidgetComponent.h"
#include "../UI/CharacterWidget.h"

// Sets default values
ABaseGameObject::ABaseGameObject()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ABaseGameObject"));
}

// Called when the game starts or when spawned
void ABaseGameObject::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseGameObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseGameObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseGameObject::Init()
{
}



APassiveGameObject::APassiveGameObject()
{
}

void APassiveGameObject::Init(EPassiveObjType Type)
{
	ObjType = Type;

	USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Robo.SK_CharM_Robo"));
	if (SkeletalMesh)
		GetMesh()->SetSkeletalMesh(SkeletalMesh);

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, 0), FRotator(0, 0, 0));

	UAnimInstance* Anim = LoadObject<UAnimInstance>(nullptr, TEXT("/Game/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));
	if (Anim)
		GetMesh()->SetAnimInstanceClass(Anim->GetClass());
}

void APassiveGameObject::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APassiveGameObject::OnBeginOverlap);
}

void APassiveGameObject::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AActiveGameObject::StaticClass()))
	{
		// Destroy();
	}
}

AActiveGameObject::AActiveGameObject()
{
	CharacterStat = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("CHARACTERSTAT"));
	
	HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HPBar->SetupAttachment(GetMesh());
	HPBar->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	HPBar->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/Book/UI/UI_HPBar.UI_HPBar_C"));
	if (UI_HUD.Succeeded())
	{
		HPBar->SetWidgetClass(UI_HUD.Class);
		HPBar->SetDrawSize(FVector2D(150.0f, 50.0f));
	}
}

void AActiveGameObject::Init(EObjType Type)
{
	ObjType = Type;
}

float AActiveGameObject::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	return ActualDamage;
}

void AActiveGameObject::Die()
{
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorEnableCollision(false);
}

void AActiveGameObject::SetIsDead(bool input)
{
	IsDead = input;
}

bool AActiveGameObject::GetIsDead()
{
	return IsDead;
}

void AActiveGameObject::BeginPlay()
{
	Super::BeginPlay();

	auto CharacterWidget = Cast<UCharacterWidget>(HPBar->GetUserWidgetObject());
	if (CharacterWidget)
		CharacterWidget->BindCharacterStat(CharacterStat);
}

void AActiveGameObject::AttackCheck()
{
	//FHitResult HitResult;
	//FCollisionQueryParams Params(NAME_None, false, this);
	////결과를 채널로 반환
	//bool bResult = GetWorld()->SweepSingleByChannel(
	//	HitResult,
	//	GetActorLocation(),
	//	GetActorLocation() + GetActorForwardVector() * 200.0f,
	//	FQuat::Identity,
	//	ECollisionChannel::ECC_GameTraceChannel2,
	//	FCollisionShape::MakeSphere(50.0f),
	//	Params);

	//if (bResult)
	//{
	//	if (HitResult.Actor.IsValid())
	//	{
	//		//UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name : %s"), *HitResult.Actor->GetName());
	//		//로그 대신 데미지
	//		FDamageEvent DamageEvent;
	//		//찾은 대상에게 50의 데미지 입히기
	//		HitResult.Actor->TakeDamage(50.0f, DamageEvent, GetController(), this);
	//	}
	//}

	//if (OutHit.GetActor()->ActorHasTag("Monster"))
	//{
	//	GameStatic->ApplyPointDamage(HitActor, 50.0f, HitActor->GetActorLocation(), OutHit, nullptr, this, nullptr); // 포인트 데미지
	//}
}