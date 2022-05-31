// Slava Ukraine

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPBasePickup.generated.h"

class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class TESTPROJECT_API ATPBasePickup : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ATPBasePickup();

    void MakePickupReachable();

    bool IsPickupReachable();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Meshes")
    UStaticMeshComponent* StandMeshComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Meshes")
    UStaticMeshComponent* MainMeshComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    USceneComponent* SceneComponent;

    void MakePickupUnreachable();
};
