// Property of Cody Cornelissen.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	//The closest distance the AI tank will bring itself to the player.
	UPROPERTY(EditDefaultsOnly, Category = AI Variables)
	float fAIFightRadius = -15.0f;

	//The distance before the AI starts to engage the target
	UPROPERTY(EditDefaultsOnly, Category = AI Variables)
	float fAIEngageRadius = 60.0f;

};
