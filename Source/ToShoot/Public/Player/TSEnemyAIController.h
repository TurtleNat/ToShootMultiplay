// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TimerManager.h"
#include "TSEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOSHOOT_API ATSEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATSEnemyAIController();
	virtual void BeginPlay() override;
	virtual void OnMoveCompleted(FAIRequestID RequestID,const FPathFollowingResult& Result) override;

protected:
	void MoveToRandomPoint();

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		float PatrolRadius = 1000.0f;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		float PatrolWaitTime = 1.0f;

	FTimerHandle PatrolTimerHandle;

};
