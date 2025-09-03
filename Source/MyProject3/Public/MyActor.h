// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class MYPROJECT3_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    // --- �ʼ� �Ķ���� ---
    UPROPERTY(EditAnywhere, Category = "Grid")
    int32 StepsToDo = 10;        // �� �̵� Ƚ��(�⺻ 10ȸ)

    UPROPERTY(EditAnywhere, Category = "Grid")
    float GridUnit = 100.f;      // ���� 1ĭ�� ���� �Ÿ�(cm)

    // ���� ���� ��ǥ
    int32 X = 0;
    int32 Y = 0;

    // --- �޼��� �и� ---
    FIntPoint Step();            // �� ������ (dx,dy) ����: -1~1, (0,0) ����
    void MoveOnce();             // ���� ���� + �α� ���
    void MoveN(int32 N);         // N�� �ݺ� �̵�
    void ApplyGridToWorld();     // (X,Y) �� ���� ��ġ �ݿ�
};
