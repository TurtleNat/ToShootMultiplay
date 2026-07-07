// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BTService_FindPlayer.h"
#include "AIController.h"
#include "Player/TSEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_FindPlayer::UBTService_FindPlayer()
{
    NodeName = TEXT("Find Player");

    Interval = 0.2f;
    RandomDeviation = 0.05f;
}

void UBTService_FindPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return;

    ATSEnemyAIController* EnemyAI = Cast<ATSEnemyAIController>(AIController);
    if (!EnemyAI) return;

    AActor* Player = EnemyAI->FindPlayer();

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp) return;

    if (Player)
    {                     
        BlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, Player);
        BlackboardComp->SetValueAsVector(TEXT("LastKnownLocation"), Player->GetActorLocation());
        UE_LOG(LogTemp, Warning, TEXT("Player Found"));
    }
    else
    {
        BlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);
        UE_LOG(LogTemp, Warning, TEXT("Player Lost"));
    }
}