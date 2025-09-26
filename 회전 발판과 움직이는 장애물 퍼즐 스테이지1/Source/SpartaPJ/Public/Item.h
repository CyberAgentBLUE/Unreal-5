#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSparta, Warning, All);

UCLASS()
class SPARTAPJ_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();

protected:
	// ===== 컴포넌트 =====
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	UStaticMeshComponent* StaticMeshComp;

	// ===== 회전(프레임 독립) =====
	/** 매 프레임 로컬 Yaw 회전 속도(도/초). 0이면 회전하지 않음 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Item|Properties")
	float RotationSpeed = 90.f;

	// ===== 왕복 이동(프레임 독립) =====
	/** 이동 사용 여부 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Item|Move")
	bool bEnableMove = true;

	/** 이동 속도(cm/s) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Item|Move")
	float MoveSpeed = 150.f;

	/** 시작 위치에서의 최대 이동 범위(cm) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Item|Move")
	float MaxRange = 300.f;

	/** 이동 방향(정규화 권장). 예: (1,0,0)=X축, (0,1,0)=Y축 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Item|Move")
	FVector MoveDirection = FVector(1, 1, 0);

	/** 왕복 기준이 되는 시작 위치(인스턴스 전용) */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Replicated, Category = "Item|Move")
	FVector StartLocation = FVector::ZeroVector;

	/** 내부 진행 부호(1 또는 -1) */
	int32 MoveSign = 1;

protected:
	// 필요 시 활성화 가능한 라이프사이클
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override; // 배치/스폰 직후
	virtual void Tick(float DeltaTime) override; // 매 프레임 호출

	// BP 연동(네 코드 유지)
	UFUNCTION(BlueprintCallable, Category = "Item|Actions")
	void ResetActorPosition();

	UFUNCTION(BlueprintPure, Category = "Item|Properties")
	float GetRotationSpeed() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Item|Event")
	void OnItemPickedUp();


	// 리플리케이션 등록
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
