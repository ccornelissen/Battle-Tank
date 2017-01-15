// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::MoveTurret(float fMoveDirection)
{
	//Clamp the move direction between one and negetive one
	float fMoveSpeed = FMath::Clamp(fMoveDirection, -1.0f, 1.0f);

	//Calculate the movement
	float fRotationSpeed = fMoveSpeed * fMaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float fRotationChange = RelativeRotation.Yaw + fRotationSpeed;

	FRotator NewRotator = FRotator(0, fRotationChange, 0);

	//Apply the movement to the turret.
	SetRelativeRotation(NewRotator);
}


