// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::MoveTurret(float fMoveDirection)
{
	//Calculate distance between current rotation and target
	float Temp = fMoveDirection;

	//Clamp the move direction between one and negetive one
	float fMoveSpeed = FMath::Clamp(fMoveDirection, -1.0f, 1.0f);

	if (Temp < -200.0f || Temp > 200.0f)
	{
		fMoveSpeed = fLastMoveSpeed;
	}

	//Calculate the movement
	float fRotationSpeed = fMoveSpeed * fMaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float fRotationChange = RelativeRotation.Yaw + fRotationSpeed;

	FRotator NewRotator = FRotator(0, fRotationChange, 0);

	//Apply the movement to the turret.
	SetRelativeRotation(NewRotator);

	fLastMoveSpeed = fMoveSpeed;
}


