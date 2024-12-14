// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/TSMenuUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "TSGameInstance.h"
#include "Player/TSBaseCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BroadcastClient.h"
#include "BroadcastServer.h"



DEFINE_LOG_CATEGORY_STATIC(LogTSMenuWidget, All, All);


void UTSMenuUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UTSMenuUserWidget::OnStartGame);
		//StartGameButton->OnClicked.AddDynamic(this, &UTSGameInstance::StartServer);

	}

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UTSMenuUserWidget::OnQuitGame);
	}

	if (QuitGameButton)
	{
		JoinGameButton->OnClicked.AddDynamic(this, &UTSMenuUserWidget::OnJoinGame);
	}
}

void UTSMenuUserWidget::OnStartGame()
{
	if (!GetWorld()) return;

	const auto TSGameInstance = GetWorld()->GetGameInstance<UTSGameInstance>();
	if(!TSGameInstance) return;

	if (TSGameInstance->GetStartupLevelName().IsNone())
	{
		return;
		UE_LOG(LogTSMenuWidget, Error, TEXT("Level name is NONE"));
	}

	
	//UGameplayStatics::OpenLevel(this, TSGameInstance->GetStartupLevelName(), true, "listen");
	UGameplayStatics::OpenLevel(GetWorld(), TSGameInstance->GetStartupLevelName(), true, "listen");

}

void UTSMenuUserWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UTSMenuUserWidget::OnJoinGame()
{

	//UGameplayStatics::OpenLevel(this, "192.168.1.100:7777", true);
	//UTSMenuUserWidget::ConnectToServer("192.168.1.100");

	//FString ServerAdress = "192.168.0.111:7777";
	//FURL URL;
	//URL.Host = ServerAdress;
	//GetWorld()->Client
	//const FString& ServerAddress = "192.168.0.111:7777";

	/*if (!ServerAddress.IsEmpty())
	{
		APlayerController* PC = GetOwningPlayer();
		if (PC)
		{
			// Подключаемся к серверу по указанному адресу
			PC->ClientTravel(ServerAddress, ETravelType::TRAVEL_Absolute);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Server address is empty!"));
	}*/
	
	FString IPAddress = "192.168.0.111"; // IP адрес сервера (для теста)
	int32 Port = 7777; // Порт сервера

	FString ConnectURL = FString::Printf(TEXT("%s:%d"), *IPAddress, Port);
	//const auto TSGameInstance = GetWorld()->GetGameInstance<UTSGameInstance>();

	// Пытаемся подключиться к серверу
	UGameplayStatics::OpenLevel(GetWorld(), FName(*ConnectURL), true);
	//UGameplayStatics::OpenLevel(GetWorld(), TSGameInstance->GetStartupLevelName(), true);
}

void UTSMenuUserWidget::ConnectToServer(const FString& ServerIP)
{
	FString Command = FString::Printf(TEXT("open %s"), *ServerIP);
	GetWorld()->Exec(GetWorld(), *Command);
}