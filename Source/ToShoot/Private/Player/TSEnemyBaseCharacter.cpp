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

  //  UE_LOG(LogTemp, Warning, TEXT("Actor Yaw: %f"), GetActorRotation().Yaw);

    const FVector Velocity = GetVelocity();

    //UE_LOG(LogTemp, Warning, TEXT("Speed=%f Velocity=%s"), Velocity.Size(), *Velocity.ToString());

    //if (!GetVelocity().IsNearlyZero())
    //{
    //    SetActorRotation(GetVelocity().Rotation());
    //}
    if (!GetVelocity().IsNearlyZero())
    {
        SetActorRotation(GetVelocity().Rotation());

        DrawDebugCoordinateSystem(
            GetWorld(),
            GetActorLocation(),
            GetActorRotation(),
            100.0f,
            false,
            -1.0f,
            0,
            2.0f
        );
    }
}

void ATSEnemyBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    //UE_LOG(LogTemp, Warning, TEXT("OrientRotationToMovement = %d"),
    //    GetCharacterMovement()->bOrientRotationToMovement); // enemy rotation on move duration

   // UE_LOG(LogTemp, Warning, TEXT("UseControllerDesiredRotation = %d"),
    //    GetCharacterMovement()->bUseControllerDesiredRotation); // enemy rotation on rotation of controller

    //UE_LOG(LogTemp, Warning, TEXT("UseControllerRotationYaw = %d"),
     //   bUseControllerRotationYaw); // enemy use YAW rotation of controller

    //UE_LOG(LogTemp, Warning, TEXT("RotationRate = %s"),
     //   *GetCharacterMovement()->RotationRate.ToString());
}
