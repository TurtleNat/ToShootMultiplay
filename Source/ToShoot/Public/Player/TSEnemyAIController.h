// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TimerManager.h"
#include "BehaviorTree/BehaviorTree.h"
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
	//UFUNCTION(BlueprintCallable)
	AActor* FindPlayer();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		float PatrolRadius = 1000.0f;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		float PatrolWaitTime = 1.0f;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		float SightRadius = 1500.f;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		float SightCheckTime = 0.2f;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		float SightAngle = 60.f;

	FTimerHandle PatrolTimerHandle;
	FTimerHandle SightTimerHandle;

	//void MoveToRandomPoint();
	

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		UBehaviorTree* BehaviorTreeAsset;
};
