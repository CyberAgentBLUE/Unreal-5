#include "SP_Pawn.h"
#include "SP_PlayerController.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputModifiers.h"      
#include "InputCoreTypes.h" 

// Sets default values
ASP_Pawn::ASP_Pawn()
{
    PrimaryActorTick.bCanEverTick = false;

    // Root: Capsule
    Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
    Capsule->InitCapsuleSize(34.f, 88.f);
    Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Capsule->SetSimulatePhysics(false);
    RootComponent = Capsule;

    // SkeletalMesh
    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SkeletalMesh->SetupAttachment(RootComponent);
    SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    SkeletalMesh->SetSimulatePhysics(false);

    // SpringArm
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 350.f;
    SpringArm->bUsePawnControlRotation = false; // 과제: 컨트롤러 회전 미사용
    SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 70.f));

    // Camera
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;

    // 자동 포제션
    AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void ASP_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASP_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASP_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (ASP_PlayerController* SP_PlayerController = Cast<ASP_PlayerController>(GetController()))
        {
            if (SP_PlayerController->IA_MOVE) EIC->BindAction(SP_PlayerController -> IA_MOVE, ETriggerEvent::Triggered, this, &ASP_Pawn::OnMove);
            if (SP_PlayerController->IA_LOOK) EIC->BindAction(SP_PlayerController -> IA_LOOK, ETriggerEvent::Triggered, this, &ASP_Pawn::OnLook);
        }
    }
}

void ASP_Pawn::OnMove(const FInputActionValue& Value)
{
    const FVector2D Input = Value.Get<FVector2D>(); // (X: 좌우, Y: 전후)
    const FVector Forward = GetActorForwardVector();
    const FVector Right = GetActorRightVector();
    const float   DT = GetWorld()->GetDeltaSeconds();

    const FVector Delta = (Forward * Input.X + Right * Input.Y) * MoveSpeed * DT;
    AddActorWorldOffset(Delta, /*bSweep=*/true);
}

void ASP_Pawn::OnLook(const FInputActionValue& Value)
{
    const FVector2D Look = Value.Get<FVector2D>(); // (X: Yaw, Y: Pitch)
    const float DT = GetWorld()->GetDeltaSeconds();

    const float YawDelta = Look.X * TurnSpeedDeg * DT;
    const float PitchDelta = -Look.Y * TurnSpeedDeg * DT; // 필요 시 부호 조정

    const FRotator DeltaRot(PitchDelta, YawDelta, 0.f);
    AddActorLocalRotation(DeltaRot);
}
