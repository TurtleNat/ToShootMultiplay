// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Weapon/Components/TSWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

// Sets default values
ASTBaseWeapon::ASTBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

	//bReplicates = true;
	//bAlwaysRelevant = true;

	WeaponFXComponent = CreateDefaultSubobject<UTSWeaponFXComponent>("TSWeaponFXComponent");


}

// Called when the game starts or when spawned
void ASTBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);

	check(WeaponFXComponent);

}

void ASTBaseWeapon::Fire()
{
	UE_LOG(LogBaseWeapon, Display, TEXT("Fire!"));

	if (MuzzleFX)
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(
			MuzzleFX,
			WeaponMesh,
			MuzzleSocketName,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::SnapToTarget,
			true
		);
	}

	MakeShot();
}

void ASTBaseWeapon::MakeShot()
{
	if (!GetWorld()) return;

	const auto Controller = GetPlayerController();
	if (!Controller) return;

	FVector ViewLocation;
	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.AddIgnoredActor(this);

	// trace from camera
	const FVector CameraTraceStart = ViewLocation;
	const FVector CameraTraceEnd = CameraTraceStart + ViewRotation.Vector() * TraceMaxDistance;

	FHitResult CameraHitResult;
	GetWorld()->LineTraceSingleByChannel(
		CameraHitResult,
		CameraTraceStart,
		CameraTraceEnd,
		ECC_Visibility,
		CollisionParams
	);

	FVector TargetPoint = CameraTraceEnd;

	if (CameraHitResult.bBlockingHit)
	{
		TargetPoint = CameraHitResult.ImpactPoint;
	}

	// trace from muzzle
	const FVector TraceStart = WeaponMesh->GetSocketLocation(MuzzleSocketName);
	const FVector ShootDirection = (TargetPoint - TraceStart).GetSafeNormal();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(
		HitResult,
		TraceStart,
		TraceEnd,
		ECC_Visibility,
		CollisionParams
	);

	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		WeaponFXComponent->PlayImpactFX(HitResult);
		DrawDebugLine(GetWorld(), TraceStart, HitResult.ImpactPoint, FColor::Red, false, 2.0f);
	}
	else
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 2.0f);
	}
}

/*void ASTBaseWeapon::MakeShot()
{
	if (!GetWorld()) return;

	const auto Controller = GetPlayerController();
	if (!Controller) return;

	FVector ViewLocation;
	FRotator ViewRotation;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner()); //player
	CollisionParams.AddIgnoredActor(this); //weapon

	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	//const FVector TraceStart = ViewLocation;
	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = ViewRotation.Vector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);

	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 3.0f);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
		WeaponFXComponent->PlayImpactFX(HitResult);
	}
	else
	{
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 3.0f, 3.0f);

	}
}*/

APlayerController* ASTBaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return nullptr;

	return Player->GetController<APlayerController>();
}


void ASTBaseWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamageActor = HitResult.GetActor();
	if (!DamageActor) return;

	DamageActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}