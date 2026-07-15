// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_LookAround.generated.h"

/**
 * 
 */

UENUM()
enum class ELookAroundState : uint8
{
    LookLeft,
    LookRight,
    ReturnCenter
};

USTRUCT()
struct FLookAroundMemory
{
    GENERATED_BODY()

    float StartYaw = 0.f;
    float TargetYaw = 0.f;
    float LookAngle = 0.f;
    ELookAroundState State = ELookAroundState::LookLeft;
    float WaitTime = 0.f;
};

UCLASS()
class TOSHOOT_API UBTTask_LookAround : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

    UBTTask_LookAround();


protected:

    virtual uint16 GetInstanceMemorySize() const override;
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

    UPROPERTY(EditAnywhere, Category = "Look Around")
        float RotationSpeed = 90.f;

    UPROPERTY(EditAnywhere, Category = "Look Around")
        float LookAngleVariation = 15.f;

};
