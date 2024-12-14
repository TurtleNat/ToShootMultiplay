// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BroadcastServer.generated.h"

UCLASS()
class TOSHOOT_API ABroadcastServer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABroadcastServer();

	UPROPERTY(EditAnywhere)
	int32 FreePort;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	class FSocket* BroadcastSocket;

	// ������� ��� ������������� ������
	void InitializeBroadcastSocket();

	// ������� ��� �������� broadcast-���������
	void SendBroadcastMessage();

	bool FindFreePort();

	// ������ ��� ������������� �������� ���������
	FTimerHandle BroadcastTimer;

	// ���� � IP-����� ��� UDP
	int32 BroadcastPort;
	FString ServerAddress;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
