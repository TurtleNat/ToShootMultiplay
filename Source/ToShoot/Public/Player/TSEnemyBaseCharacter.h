// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/TSBaseCharacter.h"
#include "TSEnemyBaseCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOSHOOT_API ATSEnemyBaseCharacter : public ATSBaseCharacter
{
	GENERATED_BODY()
	
public:
	ATSEnemyBaseCharacter(const FObjectInitializer& ObjInit);
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
};
