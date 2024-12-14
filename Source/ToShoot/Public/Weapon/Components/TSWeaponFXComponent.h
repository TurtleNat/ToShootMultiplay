// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TSWeaponFXComponent.generated.h"

class UNiagaraSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOSHOOT_API UTSWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTSWeaponFXComponent();

	void PlayImpactFX(const FHitResult& Hit);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* Effect;
};
