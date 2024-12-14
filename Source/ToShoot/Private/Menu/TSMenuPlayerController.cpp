// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/TSMenuPlayerController.h"
#include "TSGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ATSMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;

	GetWorld()->GetGameInstance<UTSGameInstance>()->TestString = "Menu level says Hello";
}
//.void ATSMenuPlayerController::SetupInputComponent()
//{
//	InputComponent->BindAction("Server", IE_Pressed, this, &ATSMenuPlayerController::StartServer);
//}


void ATSMenuPlayerController::StartServer()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Untitled"), true, "listen");
}