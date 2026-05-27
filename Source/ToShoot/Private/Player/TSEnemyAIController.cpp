// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TSEnemyAIController.h"
#include "NavigationSystem.h"
#include "NavigationSystemTypes.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

ATSEnemyAIController::ATSEnemyAIController()
{
}

void ATSEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

    APawn* ControlledPawn = GetPawn();
    if (!ControlledPawn) return;

    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()); // get NuvSys from game world
    if (!NavSys) return;

    FVector RandomPoint;

     bool bFound = NavSys->K2_GetRandomReachablePointInRadius(GetWorld(),
                                                             ControlledPawn->GetActorLocation(),
                                                             RandomPoint,
                                                             1000.0f);

    if (bFound)
    {
        MoveToLocation(RandomPoint);
    }
}