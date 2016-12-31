// Property of Cody Cornelissen.

#include "BattleTank.h"
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

bool ATankPlayerController::GetSightRayHitLocation(FVector& Vector) const
{
	FVector LookDir;

	if (GetLookDirection(LookDir))
	{
		//Setting up line trace parameters 
		FHitResult TraceHit;
		FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
		FVector StartLocation = PlayerCameraManager->GetCameraLocation();
		FVector TraceDistance = StartLocation + LookDir * fLineTraceRange;

		GetWorld()->LineTraceSingleByChannel(TraceHit, StartLocation, TraceDistance, ECollisionChannel::ECC_Visibility, TraceParams);

		if (TraceHit.bBlockingHit)
		{
			Vector = TraceHit.Location;
			return true;
		}
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector& LookDirection) const
{
	int32 iViewportSizeX, iViewportSizeY;
	GetViewportSize(iViewportSizeX, iViewportSizeY);

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
