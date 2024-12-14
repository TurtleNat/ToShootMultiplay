// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STBaseWeapon.generated.h"

class USkeletalMeshComponent;
class UTSWeaponFXComponent;

UCLASS()
class TOSHOOT_API ASTBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTBaseWeapon();

	virtual void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TraceMaxDistance = 2500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DamageAmount = 25.0f;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	UTSWeaponFXComponent* WeaponFXComponent;

	void MakeShot();
	APlayerController* GetPlayerController() const;
	void MakeDamage(const FHitResult& HitResult);

public:	
	// Called every frame
	

};
