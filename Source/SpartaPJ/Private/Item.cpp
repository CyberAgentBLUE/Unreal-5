#include "Item.h"
#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Engine/StaticMesh.h"

DEFINE_LOG_CATEGORY(LogSparta);

AItem::AItem() // 생성자
{
	PrimaryActorTick.bCanEverTick = true; // Tick 사용
	bReplicates = true;                   // 네트워크 복제

	// 루트/메쉬 생성
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
	StaticMeshComp->SetIsReplicated(true);

	// === 주석에 있던 리소스 로드 기능: 경로만 맞으면 바로 동작 ===
	// (프로젝트의 실제 경로로 바꿔주면 에디터에서 자동 적용)
	
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

	// 네가 기존에 쓰던 초기 트랜스폼 예시(유지하고 싶으면 살려두기)
	// SetActorLocation(FVector(300.0f, 200.0f, 100.0f));
	// SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
	// SetActorScale3D(FVector(2.0f, 1.0f, 1.0f));

	// 왕복 이동 기준점 저장

	StartLocation = GetActorLocation();

	// 이동 방향 보정(0이면 X축으로, 아니면 정규화)
	if (MoveDirection.IsNearlyZero())
	{
		MoveDirection = FVector(1, 0, 0);
	}
	else
	{
		MoveDirection = MoveDirection.GetSafeNormal();
	}

	// BP에서 구현한 이벤트 호출(네 코드 유지)
	OnItemPickedUp();

	UE_LOG(LogSparta, Warning, TEXT("%s BeginPlay"), *GetName());
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 회전(프레임 독립: DeltaTime 반영)
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}

	// 왕복 이동(프레임 독립)
	if (bEnableMove && MoveSpeed > 0.f && MaxRange > 0.f)
	{
		const FVector Step = MoveDirection * MoveSpeed * DeltaTime * MoveSign;
		FVector NewLoc = GetActorLocation() + Step;

		const float DistFromStart = FVector::Dist(NewLoc, StartLocation);
		if (DistFromStart > MaxRange)
		{
			// 범위 초과 시 방향 반전
			MoveSign *= -1;
			NewLoc = GetActorLocation() + (MoveDirection * MoveSpeed * DeltaTime * MoveSign);
		}

		SetActorLocation(NewLoc);
	}
}

void AItem::ResetActorPosition()
{
	// (0,0,0)으로 이동 + 시작점 재설정
	SetActorLocation(FVector::ZeroVector);
	StartLocation = GetActorLocation();
}

float AItem::GetRotationSpeed() const
{
	return RotationSpeed;
}

// 리플리케이션: Details에서 값 변경 → 플레이 중 즉시 반영
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

/* 필요하면 추가로 살릴 수 있는 훅들
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
