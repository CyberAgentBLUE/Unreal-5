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
    // --- 필수 파라미터 ---
    UPROPERTY(EditAnywhere, Category = "Grid")
    int32 StepsToDo = 10;        // 총 이동 횟수(기본 10회)

    UPROPERTY(EditAnywhere, Category = "Grid")
    float GridUnit = 100.f;      // 격자 1칸의 월드 거리(cm)

    // 현재 격자 좌표
    int32 X = 0;
    int32 Y = 0;

    // --- 메서드 분리 ---
    FIntPoint Step();            // 한 스텝의 (dx,dy) 생성: -1~1, (0,0) 금지
    void MoveOnce();             // 스텝 적용 + 로그 출력
    void MoveN(int32 N);         // N번 반복 이동
    void ApplyGridToWorld();     // (X,Y) → 월드 위치 반영
};
