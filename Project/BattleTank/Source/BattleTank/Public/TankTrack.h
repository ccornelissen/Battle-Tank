// Property of Cody Cornelissen.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Tank)
	void MoveTrack(float Throttle);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float fMaxUnitsPerSecond = 450000.0f; //Mass times desired acceleration (45000kg * 10m/s)

};
