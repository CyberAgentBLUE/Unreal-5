#include "MyActor.h"
#include "Engine/World.h"

AMyActor::AMyActor()
{
    // ƽ�� �ʼ� �ƴ�, BeginPlay�� ���
    PrimaryActorTick.bCanEverTick = false;
}

void AMyActor::BeginPlay()
{
    Super::BeginPlay();

    // ������ (0,0)���� �ʱ�ȭ �� ��ġ ����
    X = 0; Y = 0;
    ApplyGridToWorld();

    // ���� ���� �˸�
    UE_LOG(LogTemp, Log, TEXT("[Spawn] %s ���� ��ǥ=(%d,%d) ����=%s"),
        *GetName(), X, Y, *GetActorLocation().ToString());

    // �ʼ�: 10ȸ ���� �̵�
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
    // |dx|<=1, |dy|<=1, (0,0) ���� �� (0,2), (1,2) ���� �̵��� �Ұ�
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
    const FIntPoint D = Step();  // �� ���� ����
    X += D.X;
    Y += D.Y;

    ApplyGridToWorld();

    // �� ���� ���� ��ǥ ���(�ʼ�)
    UE_LOG(LogTemp, Log, TEXT("[Move] ��ǥ=(%d,%d) ����=%s ��=(%d,%d)"),
        X, Y, *GetActorLocation().ToString(), D.X, D.Y);
}

void AMyActor::MoveN(int32 N)
{
    for (int32 i = 0; i < N; ++i)
    {
        MoveOnce();
    }
    UE_LOG(LogTemp, Log, TEXT("[Done] �� %dȸ �̵� �Ϸ�. ���� ��ǥ=(%d,%d)"), N, X, Y);
}
