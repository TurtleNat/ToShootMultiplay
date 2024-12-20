// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOSHOOT_API UTSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	FString TestString = "Hello Game";
	FName GetStartupLevelName() const { return StartupLevelName; }
	FName GetMenuLevelName() const { return MenuLevelName; }
	

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName StartupLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName MenuLevelName = NAME_None;
	
};
