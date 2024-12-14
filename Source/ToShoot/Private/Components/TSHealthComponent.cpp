// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TSHealthComponent.h"
#include "GameFramework/Actor.h"
#include "OnlineSession.generated.h"

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
	//UE_LOG(BaseCharacterLog, Display, TEXT("Damage^ %f"), Damage);

	/*if (Damage <= 0.0f || IsDead()) return;
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);*/

	Health -= Damage;

	if (IsDead())
	{
		OnDeath.Broadcast();// Death report for all subscribed delegates
	}
}
