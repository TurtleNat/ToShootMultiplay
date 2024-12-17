// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TSBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/STCharacterMovementComponent.h"
#include "Components/TSHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/TSWeaponComponent.h"
#include "GameFramework/Controller.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

// Sets default values
ATSBaseCharacter::ATSBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USTCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateAbstractDefaultSubobject<UCameraComponent>("CameraComponent"); // create component
	CameraComponent->SetupAttachment(SpringArmComponent); // attach to root component (for charecter it's collision)

	HealthComponent = CreateDefaultSubobject<UTSHealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());

	WeaponComponent = CreateDefaultSubobject<UTSWeaponComponent>("WeaponComponent");
	//WeaponComponent->SetupAttachment(GetRootComponent());

	bReplicates = true;
	bAlwaysRelevant = true;
	GetMesh()->SetIsReplicated(true);
	GetCharacterMovement()->SetIsReplicated(true);

}


// Called when the game starts or when spawned
void ATSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(HealthComponent);
	check(HealthTextComponent);
	//check(GetCharacterMovement);

	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &ATSBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ATSBaseCharacter::OnHealthChanged);
}

// Called every frame
void ATSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Called to bind functionality to input
void ATSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	check(WeaponComponent); 

	PlayerInputComponent->BindAxis("MoveForward", this, &ATSBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &ATSBaseCharacter::MoveLeftRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ATSBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ATSBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATSBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ATSBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ATSBaseCharacter::OnStopRunning);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UTSWeaponComponent::Fire);
}



void ATSBaseCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ATSBaseCharacter::MoveLeftRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void ATSBaseCharacter::OnStartRunning()
{
	WantsToRun = true;
}

void ATSBaseCharacter::OnStopRunning()
{
	WantsToRun = false;
}

bool ATSBaseCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}


void ATSBaseCharacter::OnDeath()
{
	UE_LOG(LogBaseCharacter, Display, TEXT("Player is dead"));

	PlayAnimMontage(DeathAnimMontage);

	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.0f);
}

void ATSBaseCharacter::OnHealthChanged(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}


//ATSBaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) 
//{
	//Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Репликация всех необходимых переменных
	//DOREPLIFETIME(ATSBaseCharacter, HealthComponent); // Пример переменной
//}