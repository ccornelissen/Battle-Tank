// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ensure(GetPawn()))
	{
		AimComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();

		if (ensure(AimComp))
		{
			FoundAimingComponent(AimComp);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player controller cannot find the controlled tank"))
	}
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		//Get the possessed tank
		ATank* PossessedTank = Cast<ATank>(InPawn);

		if (PossessedTank)
		{
			//Attach on death function to the tank delegate
			PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnDeath);
		}
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Aim towards crosshair
	AimTowardsCrosshair();

}

void ATankPlayerController::SetViewportAdjust(float fAdjust, float fCrossHair)
{
	fViewportAdjust = fAdjust;
	fCrossHairYLocation = fCrossHair;
}

void ATankPlayerController::OnDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	//Return if aiming component is null
	if (!AimComp)
	{
		return;
	}

	FVector HitLocation; //Out parameter
	if (GetSightRayHitLocation(HitLocation)) //Casting a ray trace at the hit location
	{
		AimComp->AimAt(HitLocation);
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
		if (GetWorld()->LineTraceSingleByChannel(TraceHit, StartLocation, TraceDistance, ECollisionChannel::ECC_Camera, TraceParams))
		{
			//Set the return vector to the location it hit
			Vector = TraceHit.Location;

			//Pass the hit to the aiming component to update the reticle
			if (AimComp)
			{
				AimComp->SetAimingState(TraceHit);
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
	FVector2D ScreenLocation = FVector2D(iViewportSizeX * fCrossHairXLocation, (iViewportSizeY * fViewportAdjust)* fCrossHairYLocation);

	FVector CameraLoc;

	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLoc, LookDirection))
	{
		return true;
	}

	return false;
}
