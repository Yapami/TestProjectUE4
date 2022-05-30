// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UTPHealthComponent;

UCLASS()
class TESTPROJECT_API ATPCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ATPCharacter();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraComponent")
    UCameraComponent* CameraComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpringArmComponent")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
    UTPHealthComponent* HealthComponent;

    void MoveForward(float Amount);
    UFUNCTION(BlueprintCallable)
    void MoveRight(float Amount);

    UFUNCTION()
    void OnPlayerDead();

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
