// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TSEnemyBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"

ATSEnemyBaseCharacter::ATSEnemyBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit)

{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;

}

void ATSEnemyBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    const FVector Velocity = GetVelocity();


    if (!GetVelocity().IsNearlyZero())
    {
        SetActorRotation(GetVelocity().Rotation());

        DrawDebugCoordinateSystem(GetWorld(), GetActorLocation(), GetActorRotation(), 100.0f, false, -1.0f, 0, 2.0f);
    }
}

void ATSEnemyBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

}
