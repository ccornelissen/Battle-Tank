// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankTrack.h"

//Receives throttle from input and applies it to the tank track
void UTankTrack::MoveTrack(float Throttle)
{
	//Clamp throttle
	float fClampedThrottle = FMath::Clamp<float>(Throttle, -1.0, 1.0);

	//Get where throttle needs to be applied
	FVector AppliedForce = GetForwardVector() * fClampedThrottle * fMaxUnitsPerSecond;;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	//Apply throttle as force.
	TankRoot->AddForceAtLocation(AppliedForce, ForceLocation);
}