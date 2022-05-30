// Slava Ukraine

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDeadSignature);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTPROJECT_API UTPHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UTPHealthComponent();

    UFUNCTION(BlueprintCallable)
    void OnTakeAnyDamageFunction(AActor* DamagedActor, float Damage,
                                 const class UDamageType* DamageType,
                                 class AController* InstigatedBy, AActor* DamageCauser);

    void SetHealth(float NewHealth);

    FPlayerDeadSignature PlayerDead;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    float Health = 0.f;

    UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Health")
    float MaxHealth = 5.f;

    void OnPlayerDead();

    bool IsPlayerDead();

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;

    float GetHealth();

    UFUNCTION(BlueprintCallable)
    float GeteHealthPercent() const;
};
