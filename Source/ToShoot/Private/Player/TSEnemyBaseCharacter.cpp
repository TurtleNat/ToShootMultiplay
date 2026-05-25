// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TSEnemyBaseCharacter.h"

ATSEnemyBaseCharacter::ATSEnemyBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit)

{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}