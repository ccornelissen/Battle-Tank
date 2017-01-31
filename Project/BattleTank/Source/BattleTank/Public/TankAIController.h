// Property of Cody Cornelissen.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;
class ATank;

//Controls the owning team of the tank
UENUM(BlueprintType)
enum class EAITeam : uint8
{
	AT_Blue,
	AT_Red,
	AT_Neutral
};

/**
 *  Controls how the AI interacts with the tank and aiming component
 */

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:

	//These functions need to be public for the turret to access
	UPROPERTY(BlueprintReadWrite, Category = "Team")
	EAITeam AITeam = EAITeam::AT_Blue;

	UFUNCTION(BlueprintCallable, Category = "AI")
	void GetNearestTank();

private:

	void BeginPlay() override;

	ATank* NearestTank = nullptr;

	void Tick(float DeltaSeconds) override;

	//Tracks remaing enemies on the field
	int32 iEnemiesRemain = 0;

	//Overriding to set up delegate when pawn get controlled
	virtual void SetPawn(APawn* InPawn) override;

	//Function called on death
	UFUNCTION()
	void OnDeath();

	//The closest distance the AI tank will bring itself to the player.
	UPROPERTY(EditDefaultsOnly, Category = AIVariables)
	float fAIFightRadius = 6000.0f;

	//Controls how close the turret rotation needs to be to the player before AI will begin firing.
	UPROPERTY(EditDefaultsOnly, Category = AIVariables)
	float fAIAim = 10.0f;

	UTankAimingComponent* AimingComponent = nullptr;
};
