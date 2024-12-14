// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BroadcastClient.h"
#include "TSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOSHOOT_API ATSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void ConnectToServer(const FString& ServerAddress);

private:


	void OnPauseGame();

	class ABroadcastClient* BroadcastClientInstance;

};
