// Fill out your copyright notice in the Description page of Project Settings.


#include "BroadcastServer.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "TimerManager.h"

// Sets default values
ABroadcastServer::ABroadcastServer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bCanEverTick = false;
	BroadcastSocket = nullptr;
	BroadcastPort = 7777; // ���� ��� UDP broadcast
	ServerAddress = TEXT("192.168.0.111"); // IP-����� ������� (��� ������������)
}

// Called when the game starts or when spawned
void ABroadcastServer::BeginPlay()
{
	Super::BeginPlay();

    FindFreePort();
	InitializeBroadcastSocket();

	// ��������� ������� ��� ������������� �������� broadcast-���������
	GetWorldTimerManager().SetTimer(BroadcastTimer, this, &ABroadcastServer::SendBroadcastMessage, 1.0f, true);
	
}

void ABroadcastServer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // �������� ������
    if (BroadcastSocket)
    {
        BroadcastSocket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(BroadcastSocket);
        BroadcastSocket = nullptr;
    }
}

void ABroadcastServer::InitializeBroadcastSocket()
{
    // �������� UDP-������
    BroadcastSocket = FUdpSocketBuilder(TEXT("BroadcastSocket"))
        .AsReusable()
        .WithBroadcast()
        .Build();

    if (BroadcastSocket)
    {
        UE_LOG(LogTemp, Log, TEXT("Broadcast socket initialized."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to initialize broadcast socket."));
    }
}

void ABroadcastServer::SendBroadcastMessage()
{
    if (!BroadcastSocket)
        return;

    // ��������� ������ ��� broadcast
    FIPv4Address BroadcastAddress(192, 168, 0, 111);
    FIPv4Endpoint BroadcastEndpoint(BroadcastAddress, BroadcastPort);

    // ��������� ��� ��������
    FString Message = FString::Printf(TEXT("Server:%s:%d"), *ServerAddress, BroadcastPort);
    TArray<uint8> Data;
    Data.Append((uint8*)TCHAR_TO_UTF8(*Message), Message.Len());

    // �������� ���������
    int32 BytesSent = 0;
    BroadcastSocket->SendTo(Data.GetData(), Data.Num(), BytesSent, *BroadcastEndpoint.ToInternetAddr());

    UE_LOG(LogTemp, Log, TEXT("Broadcast message sent: %s"), *Message);
}

// Called every frame
void ABroadcastServer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABroadcastServer::FindFreePort()
{
    for (int32 Port = 1200; Port < 65535; Port++)
    {
        // ������� �����
        FSocket* TestSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_DGram, TEXT("TestSocket"), false);

        if (TestSocket)
        {
            // �������� ��������� ����� � �����
            FIPv4Endpoint Endpoint(FIPv4Address(0, 0, 0, 0), Port);
            bool bBound = TestSocket->Bind(*Endpoint.ToInternetAddr());

            if (bBound)
            {
                // ���� �������� �������, ���� ��������
                FreePort = Port;
                TestSocket->Close();
                return true;
            }

            // ������� �����, ���� �������� �� �������
            TestSocket->Close();
        }
    }

    return false; // �� ����� ��������� ����
}