// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BTTask_LookAround.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"
#include "Player/TSEnemyAIController.h"


UBTTask_LookAround::UBTTask_LookAround()
{
	NodeName = TEXT("Look Around");

	bNotifyTick = true;
}

uint16 UBTTask_LookAround::GetInstanceMemorySize() const //how much memory for instance task
{
	return sizeof(FLookAroundMemory); // For each AI, allocate memory of the size of the structure
}

EBTNodeResult::Type UBTTask_LookAround::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)// start of the task
{
	ATSEnemyAIController* EnemyAI = Cast<ATSEnemyAIController>(OwnerComp.GetAIOwner());
	if (!EnemyAI)
	{
		return EBTNodeResult::Failed;
	}

	APawn* Pawn = EnemyAI->GetPawn();
	if (!Pawn)
	{
		return EBTNodeResult::Failed;
	}

	FLookAroundMemory* Memory = reinterpret_cast<FLookAroundMemory*>(NodeMemory);

	Memory->StartYaw = Pawn->GetActorRotation().Yaw;

	const float SightAngle = EnemyAI->GetSightAngle();

	Memory->LookAngle = FMath::FRandRange(SightAngle * 0.6f, SightAngle);
	UE_LOG(LogTemp, Warning, TEXT("Look Angle = %.1f"), Memory->LookAngle);
	Memory->TargetYaw = Memory->StartYaw - SightAngle - Memory->LookAngle;

	Memory->State = ELookAroundState::LookLeft;

	return EBTNodeResult::InProgress;
}

void UBTTask_LookAround::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) // task process
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ATSEnemyAIController* EnemyAI = Cast<ATSEnemyAIController>(OwnerComp.GetAIOwner());
	if (!EnemyAI)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	APawn* Pawn = EnemyAI->GetPawn();
	if (!Pawn)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	FLookAroundMemory* Memory = reinterpret_cast<FLookAroundMemory*>(NodeMemory); // Memory for this one enemy

	FRotator CurrentRotation = Pawn->GetActorRotation();
	FRotator TargetRotation(0.f, Memory->TargetYaw, 0.f);

	FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaSeconds, RotationSpeed);

	Pawn->SetActorRotation(NewRotation);

	bool bReachedTarget = FMath::Abs(FMath::FindDeltaAngleDegrees(NewRotation.Yaw, Memory->TargetYaw)) < 1.f;

	if (!bReachedTarget)
	{
		return;
	}

	switch (Memory->State)
	{
	case ELookAroundState::LookLeft:

		Memory->TargetYaw = Memory->StartYaw + Memory->LookAngle;
		Memory->State = ELookAroundState::LookRight;
		Memory->TargetYaw = Memory->StartYaw + EnemyAI->GetSightAngle();

		break;

	case ELookAroundState::LookRight:

		Memory->TargetYaw = Memory->StartYaw;
		Memory->State = ELookAroundState::ReturnCenter;

		break;

	case ELookAroundState::ReturnCenter:

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		break;
	}
}
