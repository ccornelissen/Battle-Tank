// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	//Adding the On Hit function to the primitive component
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

//Hit component to find out if the player is touching the ground. 
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//Drive the tracks
	DriveTracks();

	//Apply the sideways force
	ApplySidewaysForce();

	//Reset the throttle
	fCurrentThrottle = 0.0f;
}

//Receives throttle from input and applies it to the tank track
void UTankTrack::SetThrottle(float Throttle)
{
	fCurrentThrottle = FMath::Clamp<float>(fCurrentThrottle + Throttle, -1.0, 1.0);
}

void UTankTrack::DriveTracks()
{
	//Get where throttle needs to be applied
	FVector AppliedForce = GetForwardVector() * fCurrentThrottle * fMaxUnitsPerSecond;;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	//Apply throttle as force.
	TankRoot->AddForceAtLocation(AppliedForce, ForceLocation);
}

//A side ways force that is applied to avoid the tank moving like it is on ice
void UTankTrack::ApplySidewaysForce()
{
	//Calculate the slippage speed
	float fSlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	//Work out the required acceleration this frame to correct
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector fCorrectionAcceleration = (-fSlippageSpeed / DeltaTime) * GetRightVector();

	//Calculate and apply sideways force (F = M * A)
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector fCorretionForce = (fCorrectionAcceleration * TankRoot->GetMass()) / 2; //Divided by the number of tracks

	TankRoot->AddForce(fCorretionForce);
}