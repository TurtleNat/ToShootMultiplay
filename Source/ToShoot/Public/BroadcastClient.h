// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BroadcastClient.generated.h"

UCLASS()
class TOSHOOT_API ABroadcastClient : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABroadcastClient();
	void CreateListenSocket();

	UPROPERTY(EditAnywhere)
	int32 CFreePort;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class FSocket* ListenSocket;

	// Функция для инициализации сокета
	void InitializeListenSocket();

	// Функция для обработки входящих сообщений
	void ReceiveBroadcastMessage();

	// Таймер для периодической проверки данных
	FTimerHandle ListenTimer;

	// Подключение клиента к серверу
	void ConnectToServer(const FString& ServerAddress, int32 ServerPort);

};
