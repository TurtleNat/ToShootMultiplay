// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TSEnemyAIController.h"
#include "NavigationSystem.h"
#include "NavigationSystemTypes.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"

ATSEnemyAIController::ATSEnemyAIController()
{
}

void ATSEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

  //  GetWorld()->GetTimerManager().SetTimer(SightTimerHandle, this, &ATSEnemyAIController::CheckPlayer, SightCheckTime, true);

   // MoveToRandomPoint();

    if (BehaviorTreeAsset)
    {
        RunBehaviorTree(BehaviorTreeAsset);
    }
}

void ATSEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);

    if (Result.Code == EPathFollowingResult::Success)
    {
 //       GetWorld()->GetTimerManager().SetTimer(PatrolTimerHandle, this, &ATSEnemyAIController::MoveToRandomPoint, PatrolWaitTime, false);
    }
}

/*void ATSEnemyAIController::MoveToRandomPoint()
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
}*/

AActor* ATSEnemyAIController::FindPlayer()
{
    APawn* ControlledPawn = GetPawn();
    if (!ControlledPawn) return nullptr;

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn) return nullptr;

    FVector EnemyLocation = ControlledPawn->GetActorLocation();
    FVector PlayerLocation = PlayerPawn->GetActorLocation();

    const FVector EnemyForwardVector = ControlledPawn->GetActorForwardVector();
    const FVector TraceStart = EnemyLocation + FVector(0.f, 0.f, 50.f);
    const FVector TraceEnd = PlayerLocation + FVector(0.f, 0.f, 50.f);
    FVector DirectionToPlayer = (PlayerLocation - EnemyLocation).GetSafeNormal();

    const float Distance = FVector::Dist(EnemyLocation, PlayerLocation);
    if (Distance  >= SightRadius) return nullptr;

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(ControlledPawn);
    FHitResult HitResult;

    float DotProduct = FVector::DotProduct(EnemyForwardVector, DirectionToPlayer);
    float MinDot = FMath::Cos(FMath::DegreesToRadians(SightAngle));

    if (DotProduct >= MinDot)
    {
        bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionParams);
        DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 0.5f, 0, 2.f);

        if (!bHit) return nullptr;

        UE_LOG(LogTemp, Warning, TEXT("Hit Actor Ptr: %p"), HitResult.GetActor());

        UE_LOG(LogTemp, Warning, TEXT("PlayerPawn Ptr: %p"), PlayerPawn);

        if (HitResult.GetActor() == PlayerPawn)
        {
            //MoveToActor(PlayerPawn);
            return PlayerPawn;
        }
    }
    return nullptr;

}

float ATSEnemyAIController::GetSightAngle() const
{
    return SightAngle;
}
