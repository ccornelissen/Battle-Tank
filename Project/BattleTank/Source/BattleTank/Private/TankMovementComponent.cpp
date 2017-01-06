// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet)
	{
		UE_LOG(LogTemp, Error, TEXT("Tracks returning null on the Tank Movement Component"));
		return;
	}

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	UE_LOG(LogTemp, Warning, TEXT("Log log log"));
}

void UTankMovementComponent::IntendMoveForward(float Speed)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}

	LeftTrack->MoveTrack(Speed);
	RightTrack->MoveTrack(Speed);

	//TODO prevent doubling of speed due to dual controls.
}

void UTankMovementComponent::IntendRotate(float Speed)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}

	LeftTrack->MoveTrack(Speed);
	RightTrack->MoveTrack(-Speed);

	//TODO prevent doubling of speed due to dual controls.
}


