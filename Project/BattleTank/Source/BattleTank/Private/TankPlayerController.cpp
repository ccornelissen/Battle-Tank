// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetControlledTank() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is set"), *GetControlledTank()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled tank returning null"))
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Aim towards crosshair
	AimTowardsCrosshair();

}

void ATankPlayerController::AimTowardsCrosshair()
{
	//Return if there is no controlled tank to aim
	if (GetControlledTank() == nullptr)
	{
		return;
	}

	FVector HitLocation; //Out parameter
	if (GetSightRayHitLocation(HitLocation)) //Casting a ray trace at the hit location
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& Vector)
{
	FVector LookDir;

	if (GetLookDirection(LookDir))
	{
		//Setting up line trace parameters 
		FHitResult TraceHit;
		FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
		FVector StartLocation = PlayerCameraManager->GetCameraLocation();
		FVector TraceDistance = StartLocation + LookDir * fLineTraceRange;

		//Check if the line trace hits anything
		if (GetWorld()->LineTraceSingleByChannel(TraceHit, StartLocation, TraceDistance, ECollisionChannel::ECC_Visibility, TraceParams))
		{
			//Set the return vector to the location it hit
			Vector = TraceHit.Location;

			//Pass the hit to the aiming component to update the reticle
			if (GetControlledTank()->TankAimingComponent != nullptr)
			{
				GetControlledTank()->TankAimingComponent->SetAimingState(TraceHit);
			}

			return true;
		}
	}

	return false;
}

//Get the direction the player is looking based on camera 
bool ATankPlayerController::GetLookDirection(FVector& LookDirection) const
{
	//Int's to hold the size of the current viewport
	int32 iViewportSizeX, iViewportSizeY;
	//Grabbing the current view port size
	GetViewportSize(iViewportSizeX, iViewportSizeY);

	//Creating a 2D vector based on viewport size times the cross hair location. Cross hair locations are public variables
	FVector2D ScreenLocation = FVector2D(iViewportSizeX * fCrossHairXLocation, iViewportSizeY * fCrossHairYLocation);

	FVector CameraLoc;

	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLoc, LookDirection))
	{
		return true;
	}

	return false;
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
