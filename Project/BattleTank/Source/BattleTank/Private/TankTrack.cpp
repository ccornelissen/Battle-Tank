// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

//TODO Fix so tank moves again

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//Calculate the slippage speed
	float fSlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	//Work out the required acceleration this frame to correct
	FVector fCorrectionAcceleration = (-fSlippageSpeed / DeltaTime) * GetRightVector();

	//Calculate and apply sideways force (F = M * A)
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector fCorretionForce = (fCorrectionAcceleration * TankRoot->GetMass()) / 2; //Divided by the number of tracks

	TankRoot->AddForce(fCorretionForce);
}

//Receives throttle from input and applies it to the tank track
void UTankTrack::MoveTrack(float Throttle)
{
	//Clamp throttle
	float fClampedThrottle = FMath::Clamp<float>(Throttle, -1.0, 1.0);

	//Get where throttle needs to be applied
	FVector AppliedForce = GetForwardVector() * fClampedThrottle * fMaxUnitsPerSecond;;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	UE_LOG(LogTemp, Warning, TEXT("%s"), *AppliedForce.ToString());

	//Apply throttle as force.
	TankRoot->AddForceAtLocation(AppliedForce, ForceLocation);
}