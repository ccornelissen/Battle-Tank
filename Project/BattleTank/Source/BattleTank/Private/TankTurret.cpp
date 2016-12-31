// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::MoveTurret(float fMoveDirection)
{
	//Clamp the move direction between one and negetive one
	float fMoveSpeed = FMath::Clamp(fMoveDirection, -1.0f, 1.0f);

	//Calculate the movement
	float fRotationChange = fMoveSpeed * fMaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float fRawChange = RelativeRotation.Yaw + fRotationChange;

	//Apply the movement to the turret.
	SetRelativeRotation(FRotator(0, fRawChange, 0));
}


