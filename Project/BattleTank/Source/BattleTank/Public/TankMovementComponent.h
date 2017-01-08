// Property of Cody Cornelissen.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Drives the tanks using references to the tanks tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:

	//Function that sets the tank tracks
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet);

	//Function that pushes the tank forward
	UFUNCTION(BlueprintCallable, Category = "Tank")
	void IntendMoveForward(float Speed);

	//Function that rotates that tank
	UFUNCTION(BlueprintCallable, Category = "Tank")
	void IntendRotate(float Speed);
	

private:
	//Function used to move the AI tank using the players movement controls, override unreals base RequestDirectMove in UNavMovementComponent
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	//References to the tank tracks
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	//Tanks forward force
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float fMoveForwardForce = 450000.0f;
};
