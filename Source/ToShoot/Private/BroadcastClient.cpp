// Fill out your copyright notice in the Description page of Project Settings.


#include "BroadcastClient.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "BroadcastServer.h"


// Sets default values
ABroadcastClient::ABroadcastClient()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ListenSocket = nullptr;
   

}

// Called when the game starts or when spawned
void ABroadcastClient::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeListenSocket();
    //CreateListenSocket();

    

	// Таймер для проверки входящих данных
	GetWorldTimerManager().SetTimer(ListenTimer, this, &ABroadcastClient::ReceiveBroadcastMessage, 0.1f, true);
}

void ABroadcastClient::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // Закрытие сокета
    if (ListenSocket)
    {
        ListenSocket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ListenSocket);
        ListenSocket = nullptr;
    }
}

void ABroadcastClient::InitializeListenSocket()
{
    // Создание UDP-сокета
    ListenSocket = FUdpSocketBuilder(TEXT("ListenSocket"))
        .AsReusable()
        .BoundToPort(7777)
        .WithReceiveBufferSize(2 * 1024 * 1024)
        .Build();

    if (ListenSocket)
    {
        UE_LOG(LogTemp, Log, TEXT("Listen socket initialized."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to initialize listen socket."));
    }
}

void ABroadcastClient::ReceiveBroadcastMessage()
{
    if (!ListenSocket)
        return;

    uint32 Size;
    while (ListenSocket->HasPendingData(Size))
    {
        TArray<uint8> ReceivedData;
        ReceivedData.SetNumUninitialized(Size);

        int32 BytesRead;
        TSharedRef<FInternetAddr> Sender = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
        ListenSocket->RecvFrom(ReceivedData.GetData(), ReceivedData.Num(), BytesRead, *Sender);

        FString ReceivedMessage = FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(ReceivedData.GetData())));
        UE_LOG(LogTemp, Log, TEXT("Received Broadcast: %s"), *ReceivedMessage);

        if (ReceivedMessage.StartsWith("Server:"))
        {
            FString ServerInfo = ReceivedMessage.RightChop(7); // Убираем "Server:"
            FString ServerIP;
            FString ServerPortStr;
            ServerInfo.Split(TEXT(":"), &ServerIP, &ServerPortStr);

            int32 ServerPort = FCString::Atoi(*ServerPortStr);
            ConnectToServer(ServerIP, ServerPort);
        }
    }
}

void ABroadcastClient::ConnectToServer(const FString& ServerAddress, int32 ServerPort)
{
    FString URL = FString::Printf(TEXT("%s:%d"), *ServerAddress, ServerPort);
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    if (PlayerController)
    {
        PlayerController->ClientTravel(URL, ETravelType::TRAVEL_Absolute);
        UE_LOG(LogTemp, Log, TEXT("Connecting to server at %s"), *URL);
    }
}

// Called every frame
void ABroadcastClient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*void ABroadcastClient::CreateListenSocket()
{
    // Получаем подсистему сокетов
    ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
    if (!SocketSubsystem)
    {
        UE_LOG(LogTemp, Error, TEXT("Socket subsystem not initialized!"));
        return;
    }

    // Создаем сокет для прослушивания (TCP)
    ListenSocket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("ListenSocket"), false);
    if (!ListenSocket)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create listen socket!"));
        return;
    }

    // Устанавливаем IP-адрес и порт
    FIPv4Address IP(192, 168, 0, 111); // 0.0.0.0 для прослушивания всех интерфейсов
    int32 Port = 7777; // Порт, на котором сервер будет слушать

    // Создаем адрес для сокета
    TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();
    Addr->SetIp(IP.Value);
    Addr->SetPort(Port);

    // Привязываем сокет к адресу
    if (!ListenSocket->Bind(*Addr))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to bind socket to port %d!"), Port);
        return;
    }

    // Запускаем прослушивание (с максимальной очередью из 8 подключений)
    if (!ListenSocket->Listen(8))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to listen on socket!"));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("Socket successfully initialized and listening on port %d"), Port);
}*/