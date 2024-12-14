// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TSMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOSHOOT_API ATSMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	void StartServer();
	
	//virtual void SetupInputComponent() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
