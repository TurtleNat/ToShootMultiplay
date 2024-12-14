// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TSWeaponComponent.h"
#include "Weapon/STBaseWeapon.h"
#include "GameFramework/Character.h"




#include "Engine/World.h"
#include "Weapon/Components/TSWeaponFXComponent.h"

// Sets default values for this component's properties
UTSWeaponComponent::UTSWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


	// ...
}


// Called when the game starts
void UTSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SpawnWeapon();
}



void UTSWeaponComponent::SpawnWeapon()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (!GetWorld()) return;

	CurrentWeapon = GetWorld()->SpawnActor<ASTBaseWeapon>(WeaponClass);
	if (!CurrentWeapon) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
	CurrentWeapon->SetOwner(Character);
}

void UTSWeaponComponent::Fire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->Fire();
}