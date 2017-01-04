// Property of Cody Cornelissen.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = SetUp)
	void Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = Tank)
	void IntendMoveForward(float Speed);

	UFUNCTION(BlueprintCallable, Category = Tank)
	void IntendRotate(float Speed);

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float fMoveForwardForce = 450000.0f;
	

};
