// Fill out your copyright notice in the Description page of Project Settings.


#include "TSGameModeBase.h"
#include "Player/TSBaseCharacter.h"
#include "Player/TSPlayerController.h"
#include "TSGameInstance.h"
//#include "Sockets.h"
//#include "SocketSubsystem.h"
//#include "Networking/Public/Common/UdpSocketBuilder.h"
//#include "IPAddress.h"
//#include "Networking/Public/Interfaces/IPv4/IPv4Endpoint.h"
//#include "Networking/Public/Interfaces/IPv4/IPv4Address.h"
#include "BroadcastServer.h"


DEFINE_LOG_CATEGORY_STATIC(LogTSGameModeBase, All, All);


ATSGameModeBase::ATSGameModeBase()
{
    DefaultPawnClass = ATSGameModeBase::StaticClass(); // property for pawn class, character inherited from pawn class
    PlayerControllerClass = ATSPlayerController::StaticClass();

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

}

void ATSGameModeBase::StartPlay()
{
    Super::StartPlay();

    UE_LOG(LogTSGameModeBase, Display, TEXT("%s"), *GetWorld()->GetGameInstance<UTSGameInstance>()->TestString);

}

void ATSGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    // Создаем экземпляр сервера
    BroadcastServerInstance = GetWorld()->SpawnActor<ABroadcastServer>(ABroadcastServer::StaticClass());
    if (BroadcastServerInstance)
    {
        UE_LOG(LogTemp, Log, TEXT("Broadcast server initialized in GameMode."));
    }
}