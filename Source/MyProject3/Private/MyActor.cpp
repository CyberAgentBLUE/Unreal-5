#include "MyActor.h"
#include "Engine/World.h"

AMyActor::AMyActor()
{
    // 틱은 필수 아님, BeginPlay만 사용
    PrimaryActorTick.bCanEverTick = false;
}

void AMyActor::BeginPlay()
{
    Super::BeginPlay();

    // 시작점 (0,0)으로 초기화 후 위치 적용
    X = 0; Y = 0;
    ApplyGridToWorld();

    // 스폰 시점 알림
    UE_LOG(LogTemp, Log, TEXT("[Spawn] %s 시작 좌표=(%d,%d) 월드=%s"),
        *GetName(), X, Y, *GetActorLocation().ToString());

    // 필수: 10회 랜덤 이동
    MoveN(StepsToDo);
}

void AMyActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyActor::ApplyGridToWorld()
{
    SetActorLocation(FVector(X * GridUnit, Y * GridUnit, 0.f));
}

FIntPoint AMyActor::Step()
{
    // |dx|<=1, |dy|<=1, (0,0) 금지 → (0,2), (1,2) 같은 이동은 불가
    int32 dx = 0, dy = 0;
    do
    {
        dx = FMath::RandRange(-1, 1);
        dy = FMath::RandRange(-1, 1);
    } while (dx == 0 && dy == 0);

    return FIntPoint(dx, dy);
}

void AMyActor::MoveOnce()
{
    const FIntPoint D = Step();  // 한 스텝 생성
    X += D.X;
    Y += D.Y;

    ApplyGridToWorld();

    // 매 스텝 현재 좌표 출력(필수)
    UE_LOG(LogTemp, Log, TEXT("[Move] 좌표=(%d,%d) 월드=%s Δ=(%d,%d)"),
        X, Y, *GetActorLocation().ToString(), D.X, D.Y);
}

void AMyActor::MoveN(int32 N)
{
    for (int32 i = 0; i < N; ++i)
    {
        MoveOnce();
    }
    UE_LOG(LogTemp, Log, TEXT("[Done] 총 %d회 이동 완료. 최종 좌표=(%d,%d)"), N, X, Y);
}
