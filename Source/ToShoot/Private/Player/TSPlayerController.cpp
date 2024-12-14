// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TSPlayerController.h"
#include "TSGameInstance.h"
#include "BroadcastClient.h"



void ATSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//SetInputMode(FInputModeUIOnly());
	SetInputMode(FInputModeGameOnly());

	// Создаем экземпляр клиента
	BroadcastClientInstance = GetWorld()->SpawnActor<ABroadcastClient>(ABroadcastClient::StaticClass());
	if (BroadcastClientInstance)
	{
		UE_LOG(LogTemp, Log, TEXT("Broadcast client initialized for player."));
	}
}

void ATSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent) return;

	InputComponent->BindAction("TagMouse", IE_Pressed, this, &ATSPlayerController::OnPauseGame);

	bReplicates = true;
	bAlwaysRelevant = true;
}

void ATSPlayerController::OnPauseGame()
{
	bShowMouseCursor = true;
}

void ATSPlayerController::ConnectToServer(const FString& ServerAddress)
{
	if (GetWorld())
	{
		FString Command = FString::Printf(TEXT("open %s"), *ServerAddress);
		GetWorld()->Exec(GetWorld(), *Command);
	}
}

