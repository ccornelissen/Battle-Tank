// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::ElevateBarrel(float DegreesPerSecond)
{
	float fMoveSpeed = FMath::Clamp(DegreesPerSecond, -1.0f, 1.0f);

	float fElevationChange = fMoveSpeed * fMaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	float fRawElevation = RelativeRotation.Pitch + fElevationChange;

	float fClampedElevation = FMath::Clamp(fRawElevation, fMinHeight, fMaxHeight);
	SetRelativeRotation(FRotator(fClampedElevation, 0, 0));
}


