// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TSWeaponComponent.generated.h"

class ASTBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOSHOOT_API UTSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTSWeaponComponent();

	void Fire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASTBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttachPointName = "WeaponSocket";

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY()
	ASTBaseWeapon* CurrentWeapon = nullptr;

	void SpawnWeapon();
		
};
