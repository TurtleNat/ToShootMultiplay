// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BroadcastServer.h"
#include "TSGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class TOSHOOT_API ATSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATSGameModeBase();


protected:
	
	virtual void StartPlay() override;
	virtual void BeginPlay() override;
	
	

private:

	//AServerTSGameModeBase* BroadcastServer;
	UPROPERTY()
	class ABroadcastServer* BroadcastServerInstance;

};
