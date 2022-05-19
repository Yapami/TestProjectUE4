// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TPCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATPCharacter::ATPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->TargetArmLength = 200.f;
    SpringArmComponent->SocketOffset.Z = 75.f;
    SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

}

// Called when the game starts or when spawned
void ATPCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void ATPCharacter::Jump()
{
    Super::Jump();
}

