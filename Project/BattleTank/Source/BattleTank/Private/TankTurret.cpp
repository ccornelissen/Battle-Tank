// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::MoveTurret(float fMoveDirection)
{
	//TODO Fix this shit 
	////Figure out rotation difference bettween new location and current
	//float fRotDifference = fMoveDirection - RelativeRotation.Yaw;

	//Clamp the move direction between one and negetive one
	//float fMoveSpeed = FMath::Clamp(fMoveDirection, -1.0f, 1.0f);

	////If difference is too small do not both with checks to continue same rotation.
	//if ((fRotDifference > 50.0f || fRotDifference < -50.0f) || (RelativeRotation.Yaw < 145 && RelativeRotation.Yaw > -145))
	//{
	//	if (fLastKnownMoveSpeed < 0.0f && RelativeRotation.Yaw < -30 && RelativeRotation.Yaw > -220)
	//	{
	//		fMoveSpeed = -1.0f;
	//	}
	//	else if (fLastKnownMoveSpeed > 0.0f && RelativeRotation.Yaw > 30 && RelativeRotation.Yaw < 220)
	//	{
	//		fMoveSpeed = 1.0f;
	//	}
	//}

	//Calculate the movement
	float fRotationChange = fMaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float fRawChange = RelativeRotation.Yaw + fRotationChange;

	FRotator StartLocation = FRotator(0, RelativeRotation.Yaw, 0);
	FRotator EndLocation = FRotator(0, fMoveDirection, 0);

	FRotator NewLocation = FMath::RInterpTo(StartLocation, EndLocation, GetWorld()->GetTimeSeconds(), fMaxDegreesPerSecond);

	//Apply the movement to the turret.
	SetRelativeRotation(FRotator(0.0f, NewLocation.Yaw, 0.0f));

	//fLastKnownMoveSpeed = fMoveSpeed;
}


