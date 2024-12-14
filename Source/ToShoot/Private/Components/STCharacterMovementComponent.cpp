// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STCharacterMovementComponent.h"
#include "Player/TSBaseCharacter.h"

float USTCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ATSBaseCharacter* Player = Cast<ATSBaseCharacter>(GetPawnOwner());
    return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}