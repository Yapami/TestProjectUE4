// Slava Ukraine

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "TPBasePickup.generated.h"

UCLASS()
class TESTPROJECT_API ATPBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPBasePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stand")
    UStaticMeshComponent* StandMeshComponent;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USceneComponent* SceneComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
