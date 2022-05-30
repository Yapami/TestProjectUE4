// Slava Ukraine

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUCoreTypes.h"
#include "TPPlayerHUD.generated.h"


/**
 *
 */
UCLASS()
class TESTPROJECT_API ATPPlayerHUD : public AHUD
{
    GENERATED_BODY()
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerDeadWidgetClass;

    virtual void BeginPlay() override;

public:
    UFUNCTION()
    void UpdateGameTime(float Time);

    UFUNCTION()
    void ChangeWidget(EGameState GameState1);

private:
    UUserWidget* PlayerHUDWidget;
    UUserWidget* PlayerDeadWidget;

    EGameState GameState;
};
