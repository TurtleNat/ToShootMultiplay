// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Weapon/Components/TSWeaponFXComponent.h"


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

	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	const FVector TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
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
}

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