// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/TPCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/TPHealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TPGameModeBase.h"

// Sets default values
ATPCharacter::ATPCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance
    // if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    check(SpringArmComponent);
    SpringArmComponent->SetupAttachment(GetRootComponent());

    // Spring Arm Component settings:
    SpringArmComponent->TargetArmLength = 200.f;
    SpringArmComponent->SocketOffset.Z = 75.f;
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    check(CameraComponent);
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<UTPHealthComponent>("HealthComponent");
    check(HealthComponent);
}

float ATPCharacter::GetNormalSpeed() const
{
    return NormalSpeed;
}

float ATPCharacter::GetMaxWalkSpeed() const
{
    return GetCharacterMovement()->MaxWalkSpeed;
}

void ATPCharacter::SetMaxWalkSpeed(float Speed)
{
    GetCharacterMovement()->MaxWalkSpeed = Speed;
}

// Called when the game starts or when spawned
void ATPCharacter::BeginPlay()
{
    Super::BeginPlay();

    OnTakeAnyDamage.AddDynamic(HealthComponent, &UTPHealthComponent::OnTakeAnyDamage);

    ATPGameModeBase* GameMode = Cast<ATPGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode)
    {
        return;
    }
    GameMode->OnChangeGameState.AddDynamic(this, &ATPCharacter::OnPlayerDead);

    SetMaxWalkSpeed(GetNormalSpeed());

    GameMode->SetupGameStatePlayerAlive();
}

// Called to bind functionality to input
void ATPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    InputComponent->BindAxis("MoveForward", this, &ATPCharacter::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &ATPCharacter::MoveRight);
    InputComponent->BindAxis("MouseY", this, &ATPCharacter::AddControllerPitchInput);
    InputComponent->BindAxis("MouseX", this, &ATPCharacter::AddControllerYawInput);
    InputComponent->BindAction("Jump", IE_Pressed, this, &ATPCharacter::Jump);
}

void ATPCharacter::MoveForward(float Amount)
{
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ATPCharacter::MoveRight(float Amount)
{
    AddMovementInput(GetActorRightVector(), Amount);
}

void ATPCharacter::OnPlayerDead(EGameState GameState)
{
    if (GameState == EGameState::PlayerIsDead)
    {
        Destroy();
    }
}
