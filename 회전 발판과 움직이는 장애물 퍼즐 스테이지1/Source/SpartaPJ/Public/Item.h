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
	// ===== ������Ʈ =====
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	UStaticMeshComponent* StaticMeshComp;

	// ===== ȸ��(������ ����) =====
	/** �� ������ ���� Yaw ȸ�� �ӵ�(��/��). 0�̸� ȸ������ ���� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Item|Properties")
	float RotationSpeed = 90.f;

	// ===== �պ� �̵�(������ ����) =====
	/** �̵� ��� ���� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Item|Move")
	bool bEnableMove = true;

	/** �̵� �ӵ�(cm/s) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Item|Move")
	float MoveSpeed = 150.f;

	/** ���� ��ġ������ �ִ� �̵� ����(cm) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Item|Move")
	float MaxRange = 300.f;

	/** �̵� ����(����ȭ ����). ��: (1,0,0)=X��, (0,1,0)=Y�� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Item|Move")
	FVector MoveDirection = FVector(1, 1, 0);

	/** �պ� ������ �Ǵ� ���� ��ġ(�ν��Ͻ� ����) */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Replicated, Category = "Item|Move")
	FVector StartLocation = FVector::ZeroVector;

	/** ���� ���� ��ȣ(1 �Ǵ� -1) */
	int32 MoveSign = 1;

protected:
	// �ʿ� �� Ȱ��ȭ ������ ����������Ŭ
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override; // ��ġ/���� ����
	virtual void Tick(float DeltaTime) override; // �� ������ ȣ��

	// BP ����(�� �ڵ� ����)
	UFUNCTION(BlueprintCallable, Category = "Item|Actions")
	void ResetActorPosition();

	UFUNCTION(BlueprintPure, Category = "Item|Properties")
	float GetRotationSpeed() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Item|Event")
	void OnItemPickedUp();


	// ���ø����̼� ���
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
