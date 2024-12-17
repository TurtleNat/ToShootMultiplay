// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TSHealthComponent.h"
#include "GameFramework/Actor.h"
#include "OnlineSession.generated.h"
#include "Dev/TSFireDamageType.h"
#include "Dev/TSIceDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

// Sets default values for this component's properties
UTSHealthComponent::UTSHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}
  

// Called when the game starts
void UTSHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth);

	Health = MaxHealth;
	OnHealthChanged.Broadcast(Health);
	// ...
	
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UTSHealthComponent::OnTakeAnyDamage);
	}
}


// Called every frame
void UTSHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UTSHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead()) return;
;
	Health -= Damage;
	OnHealthChanged.Broadcast(Health);

	if (IsDead())
	{
		OnDeath.Broadcast();// Death report for all subscribed delegates
	}
}
