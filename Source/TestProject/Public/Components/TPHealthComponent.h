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

    FPlayerDeadSignature PlayerDead; //TO DO

    UFUNCTION(BlueprintCallable)
    void OnTakeAnyDamage(AActor* DamagedActor, float Damage,
                                 const class UDamageType* DamageType,
                                 class AController* InstigatedBy, AActor* DamageCauser);

    UFUNCTION(BlueprintCallable)
    float GeteHealthPercent() const;

    void SetHealth(float NewHealth);

    float GetHealth() const;

protected:
    UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Health")
    float MaxHealth = 100.f;

    float Health = 0.f;

    void OnPlayerDead();

    bool IsPlayerDead();
};
