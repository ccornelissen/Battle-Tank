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

	UPROPERTY(EditAnywhere, Category = "Setup")
	float fMaxDegreesPerSecond = 20.0f;

	float fLastMoveSpeed = 0;
};
