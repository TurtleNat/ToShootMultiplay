// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TSHealthComponent.h"
#include "GameFramework/Actor.h"
#include "OnlineSession.generated.h"
#include "Dev/TSFireDamageType.h"
#include "Dev/TSIceDamageType.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

// Sets default values for this component's properties
UTSHealthComponent::UTSHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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
		//ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UTSHealthComponent::DoHeal);
	}
}


// Called every frame
void UTSHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//DoHeal();
}



void UTSHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (GetWorld()->GetTimerManager().IsTimerActive(OnStartHealTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(OnStartHealTimer);
	}

	if (Damage <= 0.0f || IsDead()) return;
;
	Health -= Damage;
	OnHealthChanged.Broadcast(Health);

	if (IsDead())
	{
		OnDeath.Broadcast();// Death report for all subscribed delegates
	}

	if (!IsDead())
	{
		GetWorld()->GetTimerManager().SetTimer(OnStartHealTimer, this, &UTSHealthComponent::DoHeal, HealDelayTime, false);
	}
}

void UTSHealthComponent::DoHeal( )
{
	//if ((0.0f < Health) && (Health < 100.0f))
	if((Health < 100.0f) )
	{
		Health = Health + HealModifier;
		OnHealthChanged.Broadcast(Health);
	}

	if (!(GetWorld()->GetTimerManager().IsTimerActive(OnStepHealTimer)) && (Health < 100.0f))
	{
		GetWorld()->GetTimerManager().SetTimer(OnStepHealTimer, this, &UTSHealthComponent::DoHeal, HealUpdateTime, true);
	}

	if ((GetWorld()->GetTimerManager().IsTimerActive(OnStepHealTimer)) && (Health == 100.0f))
	{
		GetWorld()->GetTimerManager().ClearTimer(OnStepHealTimer);
	}
}
