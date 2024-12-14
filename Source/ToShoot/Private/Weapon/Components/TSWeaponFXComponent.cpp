// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Components/TSWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values for this component's properties
UTSWeaponFXComponent::UTSWeaponFXComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

 
	// ...
}

void UTSWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}

