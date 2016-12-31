// Property of Cody Cornelissen.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), HideCategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void ElevateBarrel(float DegreesPerSecond);

	UPROPERTY(EditAnywhere, Category = "Setup")
	float fMaxDegreesPerSecond = 20.0f;

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float fMaxHeight = 40.0f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float fMinHeight = -40.0f;
	
	
};
