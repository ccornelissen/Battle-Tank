// Property of Cody Cornelissen.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), HideCategories = ("Collision"))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	void MoveTurret(float fMoveDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float fMaxDegreesPerSecond = 30.0f;
};
