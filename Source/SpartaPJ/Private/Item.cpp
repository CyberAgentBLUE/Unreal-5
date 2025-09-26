#include "Item.h"
#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Engine/StaticMesh.h"

DEFINE_LOG_CATEGORY(LogSparta);

AItem::AItem() // ������
{
	PrimaryActorTick.bCanEverTick = true; // Tick ���
	bReplicates = true;                   // ��Ʈ��ũ ����

	// ��Ʈ/�޽� ����
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
	StaticMeshComp->SetIsReplicated(true);

	// === �ּ��� �ִ� ���ҽ� �ε� ���: ��θ� ������ �ٷ� ���� ===
	// (������Ʈ�� ���� ��η� �ٲ��ָ� �����Ϳ��� �ڵ� ����)
	
	/*static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
		TEXT("/Game/Resources/Props/SM_Chair.SM_Chair"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(
		TEXT("/Game/Resources/Materials/M_RMA_Master.M_RMA_Master"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}*/
	
}

void AItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(LogSparta, Warning, TEXT("%s PostInitializeComponents"), *GetName());
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	// �װ� ������ ���� �ʱ� Ʈ������ ����(�����ϰ� ������ ����α�)
	// SetActorLocation(FVector(300.0f, 200.0f, 100.0f));
	// SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
	// SetActorScale3D(FVector(2.0f, 1.0f, 1.0f));

	// �պ� �̵� ������ ����

	StartLocation = GetActorLocation();

	// �̵� ���� ����(0�̸� X������, �ƴϸ� ����ȭ)
	if (MoveDirection.IsNearlyZero())
	{
		MoveDirection = FVector(1, 0, 0);
	}
	else
	{
		MoveDirection = MoveDirection.GetSafeNormal();
	}

	// BP���� ������ �̺�Ʈ ȣ��(�� �ڵ� ����)
	OnItemPickedUp();

	UE_LOG(LogSparta, Warning, TEXT("%s BeginPlay"), *GetName());
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ȸ��(������ ����: DeltaTime �ݿ�)
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}

	// �պ� �̵�(������ ����)
	if (bEnableMove && MoveSpeed > 0.f && MaxRange > 0.f)
	{
		const FVector Step = MoveDirection * MoveSpeed * DeltaTime * MoveSign;
		FVector NewLoc = GetActorLocation() + Step;

		const float DistFromStart = FVector::Dist(NewLoc, StartLocation);
		if (DistFromStart > MaxRange)
		{
			// ���� �ʰ� �� ���� ����
			MoveSign *= -1;
			NewLoc = GetActorLocation() + (MoveDirection * MoveSpeed * DeltaTime * MoveSign);
		}

		SetActorLocation(NewLoc);
	}
}

void AItem::ResetActorPosition()
{
	// (0,0,0)���� �̵� + ������ �缳��
	SetActorLocation(FVector::ZeroVector);
	StartLocation = GetActorLocation();
}

float AItem::GetRotationSpeed() const
{
	return RotationSpeed;
}

// ���ø����̼�: Details���� �� ���� �� �÷��� �� ��� �ݿ�
void AItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AItem, RotationSpeed);
	DOREPLIFETIME(AItem, bEnableMove);
	DOREPLIFETIME(AItem, MoveSpeed);
	DOREPLIFETIME(AItem, MaxRange);
	DOREPLIFETIME(AItem, MoveDirection);
	DOREPLIFETIME(AItem, StartLocation);
}

/* �ʿ��ϸ� �߰��� �츱 �� �ִ� �ŵ�
void AItem::Destroyed()
{
	UE_LOG(LogSparta, Warning, TEXT("%s Destroyed"), *GetName());
	Super::Destroyed();
}

void AItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogSparta, Warning, TEXT("%s EndPlay"), *GetName());
	Super::EndPlay(EndPlayReason);
}
*/
