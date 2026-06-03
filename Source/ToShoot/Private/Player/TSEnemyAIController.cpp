// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TSEnemyAIController.h"
#include "NavigationSystem.h"
#include "NavigationSystemTypes.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATSEnemyAIController::ATSEnemyAIController()
{
}

void ATSEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

    MoveToRandomPoint();
}

void ATSEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);

    if (Result.Code == EPathFollowingResult::Success)
    {
        GetWorld()->GetTimerManager().SetTimer(PatrolTimerHandle, this, &ATSEnemyAIController::MoveToRandomPoint, PatrolWaitTime, false);
    }
}

void ATSEnemyAIController::MoveToRandomPoint()
{
    APawn* ControlledPawn = GetPawn();
    if (!ControlledPawn) return;

    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()); // get NuvSys from game world
    if (!NavSys) return;

    FVector RandomPoint;

    bool bFound = NavSys->K2_GetRandomReachablePointInRadius(GetWorld(),
        ControlledPawn->GetActorLocation(),
        RandomPoint,
        PatrolRadius);

    if (bFound)
    {
        MoveToLocation(RandomPoint);
    }
}
