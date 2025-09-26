// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_GameModeBase.h"
#include "SP_Pawn.h"

ASP_GameModeBase::ASP_GameModeBase()
{
	DefaultPawnClass = ASP_Pawn::StaticClass();
	PlayerControllerClass = ASP_Pawn::StaticClass();
}

