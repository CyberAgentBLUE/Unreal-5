#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "SP_Pawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class RUN_API ASP_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASP_Pawn();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCapsuleComponent* Capsule;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USkeletalMeshComponent* SkeletalMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCameraComponent* Camera;

    // Enhanced Input
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputMappingContext* IMC_Default;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_MOVE;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_LOOK;

    // Movement values
    UPROPERTY(EditAnywhere, Category = "Movement")
    float MoveSpeed = 500.f;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float TurnSpeedDeg = 180.f;


private:
    void OnMove(const FInputActionValue& Value);
    void OnLook(const FInputActionValue& Value);

};
