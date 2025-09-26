// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_PlayerController.h"
#include "EnhancedInputSubsystems.h" // Enhanced Input System의 Local Player Subsystem을 사용하기 위해 포함

ASP_PlayerController::ASP_PlayerController()
	:InputMappingContext(nullptr),
	IA_MOVE(nullptr),
	IA_LOOK(nullptr)
{}
void ASP_PlayerController::BeginPlay()
{
    Super::BeginPlay();
    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (InputMappingContext)
            {
                Subsystem->AddMappingContext(InputMappingContext, 0);
            }
        }
    }
}

