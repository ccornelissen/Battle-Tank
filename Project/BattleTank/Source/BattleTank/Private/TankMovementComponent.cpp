// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet || !RightTrackToSet)) //null check
	{
		UE_LOG(LogTemp, Error, TEXT("Tracks returning null on the Tank Movement Component"));
		return;
	}

	//Variables passed through tank blueprint
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//Vector in the direction the AI would like to move
	FVector AINormalVector = MoveVelocity.GetSafeNormal();

	//Getting the current forward direction of the AI controlled tank
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	//Getting the dot product to find how parallel the 2 vectors are, which will drive the movement velocity.
	float fForward = FVector::DotProduct(AINormalVector, TankForward);

	//Telling the tank to move with our found float
	IntendMoveForward(fForward);

	//Getting the cross product to find the tanks "perpandicularity"
	FVector TankCross = FVector::CrossProduct(TankForward, AINormalVector);

	//Rotate based on the Z
	IntendRotate(TankCross.Z);
}

void UTankMovementComponent::IntendMoveForward(float Speed)
{
	if (!ensure(LeftTrack || !RightTrack))
	{
		return;
	}

	//Applying speed equally to both tracks as the player wants to move forward.
	LeftTrack->MoveTrack(Speed);
	RightTrack->MoveTrack(Speed);

	//TODO prevent doubling of speed due to dual controls.
}

void UTankMovementComponent::IntendRotate(float Speed)
{
	if (!ensure(LeftTrack || !RightTrack))
	{
		return;
	}

	//Rotating to the right, right track moves backwards, left forwards, rotating the tank
	LeftTrack->MoveTrack(Speed);
	RightTrack->MoveTrack(-Speed);

	//TODO prevent doubling of speed due to dual controls.
}


