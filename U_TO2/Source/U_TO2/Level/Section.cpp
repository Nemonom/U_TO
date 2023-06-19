#include "Section.h"
#include "../../U_TO2/GameObject/Enemy/EnemyManager.h"
#include "../../U_TO2/GameObject/Enemy/EnemyObject.h"
#include "../../U_TO2/Item/ItemObject.h"
#include "../../U_TO2/GameObject/Player/PlayerObject.h"

ASection::ASection()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;

	FString AssetPath = TEXT("/Game/Book/StaticMesh/SM_SQUARE.SM_SQUARE");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SQUARE(*AssetPath);
	if (SM_SQUARE.Succeeded())
	{
		Mesh->SetStaticMesh(SM_SQUARE.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load staticmesh asset. : %s"), *AssetPath);
	}

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Trigger->SetBoxExtent(FVector(775.0f, 775.0f, 300.0f));
	Trigger->SetupAttachment(RootComponent);
	Trigger->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	Trigger->SetCollisionProfileName(TEXT("NoCollision"));

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASection::OnTriggerBeginOverlap);

	FString GateAssetPath = TEXT("/Game/Book/StaticMesh/SM_GATE.SM_GATE");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_GATE(*GateAssetPath);
	if (!SM_GATE.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load staticmesh asset. : %s"), *GateAssetPath);
	}

	static FName GateSockets[] = { {TEXT("+XGate")}, {TEXT("-XGate")}, {TEXT("+YGate")}, {TEXT("-YGate")} };
	for (FName GateSocket : GateSockets)
	{
		if (false == Mesh->DoesSocketExist(GateSocket))
			continue;

		UStaticMeshComponent* NewGate = CreateDefaultSubobject<UStaticMeshComponent>(*GateSocket.ToString());
		NewGate->SetStaticMesh(SM_GATE.Object);
		NewGate->SetupAttachment(RootComponent, GateSocket);
		NewGate->SetRelativeLocation(FVector(0.0f, -80.5f, 0.0f));
		GateMeshes.Add(NewGate);

		UBoxComponent* NewGateTrigger = CreateDefaultSubobject<UBoxComponent>(*GateSocket.ToString().Append(TEXT("Trigger")));
		NewGateTrigger->SetBoxExtent(FVector(100.0f, 100.0f, 300.0f));
		NewGateTrigger->SetupAttachment(RootComponent, GateSocket);
		NewGateTrigger->SetRelativeLocation(FVector(70.0f, 0.0f, 250.0f));
		NewGateTrigger->SetCollisionProfileName(TEXT("GateTrigger"));
		GateTriggers.Add(NewGateTrigger);

		NewGateTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASection::OnGateTriggerBeginOverlap);
		NewGateTrigger->ComponentTags.Add(GateSocket);
	}

	EnemyManager_ = nullptr;
}

void ASection::SetBattleSection(bool bIsBattleSection)
{
	IsBattleSection = bIsBattleSection;
}

void ASection::BeginPlay()
{
	Super::BeginPlay();

	SetState(ESectionState::COMPLETE);
}


void ASection::SetState(ESectionState NewState)
{
	switch (NewState)
	{
	case ESectionState::READY:
	{
		EnemyManager_ = nullptr;

		Trigger->SetCollisionProfileName(TEXT("GateTrigger"));
		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
		}

		OperateGates(true);
	}
	break;
	case ESectionState::BATTLE:
	{
		EnemyManager_ = new EnemyManager(GetWorld(), Mesh->GetComponentLocation());
		auto Boss = EnemyManager_->GetBoss();
		if (Boss)
			Boss->OnDestroyed.AddDynamic(this, &ASection::OnBossDestroyed);

		Trigger->SetCollisionProfileName(TEXT("NoCollision"));
		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
		}

		OperateGates(false);

		GetWorld()->GetTimerManager().SetTimer(SpawnItemBoxTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
			GetWorld()->SpawnActor<AItemObject>(GetActorLocation() + FVector(FMath::RandPointInCircle(600.0f), 30.0f), FRotator::ZeroRotator);
			}), 5.0f, false);
	}
	break;
	case ESectionState::COMPLETE:
	{
		Trigger->SetCollisionProfileName(TEXT("NoCollision"));
		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			GateTrigger->SetCollisionProfileName(TEXT("GateTrigger"));
		}

		OperateGates(true);

		if (EnemyManager_)
			EnemyManager_->KillAllEnemy();
	}
	break;
	}

	CurrentState = NewState;
}

void ASection::OperateGates(bool bOpen)
{
	for (UStaticMeshComponent* Gate : GateMeshes)
	{
		Gate->SetRelativeRotation(bOpen ? FRotator(0.0f, -90.0f, 0.0f) : FRotator::ZeroRotator);
	}
}

void ASection::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerObject::StaticClass()))
	{
		ESectionState TempState = IsBattleSection ? ESectionState::BATTLE : ESectionState::COMPLETE;
		SetState(TempState);
	}
}

void ASection::OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FName ComponentTag = OverlappedComponent->ComponentTags[0];
	FName SocketName = FName(*ComponentTag.ToString().Left(2));
	if (!Mesh->DoesSocketExist(SocketName))
		return;

	FVector NewLocation = Mesh->GetSocketLocation(SocketName);

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	FCollisionObjectQueryParams ObjectQueryParam(FCollisionObjectQueryParams::InitType::AllObjects);
	bool bResult = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		NewLocation,
		FQuat::Identity,
		ObjectQueryParam,
		FCollisionShape::MakeSphere(775.0f),
		CollisionQueryParam
	);

	if (!bResult)
	{
		auto NewSection = GetWorld()->SpawnActor<ASection>(NewLocation, FRotator::ZeroRotator);
		NewSection->SetBattleSection(true);
		NewSection->SetState(ESectionState::READY);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("New section area is not empty."));
	}
}

void ASection::OnBossDestroyed(AActor* DestroyedActor)
{
	SetState(ESectionState::COMPLETE);
}

void ASection::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	delete EnemyManager_;
	EnemyManager_ = nullptr;
}

// Called every frame
void ASection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

