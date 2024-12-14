// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/TSMenuGameModeBase.h"
#include "Menu/TSMenuPlayerController.h"
#include "Menu/UI/TSMenuHUD.h"
#include "TSGameInstance.h"



ATSMenuGameModeBase::ATSMenuGameModeBase()
{
	PlayerControllerClass = ATSMenuGameModeBase::StaticClass();
	HUDClass = ATSMenuHUD::StaticClass();
	//InputComponent->BindAction("Server", IE_Pressed, this, UTSGameInstance::StartServer);
}

