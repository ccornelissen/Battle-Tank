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

void ATankPlayerController::SetViewportAdjust(float Viewport)
{
	fViewportAdjust = Viewport;
}

int32 ATankPlayerController::RedTeamNumber()
{
	int32 RedTanks = 0;

	for (TActorIterator<ATank> TankItr(GetWorld()); TankItr; ++TankItr)
	{
		//Go through tanks in the world
		if (TankItr)
		{
			if (TankItr->TankTeam == ETankTeam::TT_Red)
			{
				RedTanks++;
			}
		}
	}

	return RedTanks;
}

int32 ATankPlayerController::BlueTeamNumber()
{
	int32 BlueTanks = 0;

	for (TActorIterator<ATank> TankItr(GetWorld()); TankItr; ++TankItr)
	{
		//Go through tanks in the world
		if (TankItr)
		{
			if (TankItr->TankTeam == ETankTeam::TT_Blue)
			{
				BlueTanks++;
			}
		}
	}

	return BlueTanks;
}

void ATankPlayerController::RemovePlayerTwo()
{
	const int iMaxSplitScreen = 1;
	ULocalPlayer* PlayersToRemove[iMaxSplitScreen];
	int iRemIndex = 0;

	for (FConstPlayerControllerIterator Iterator = GEngine->GameViewport->GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* Controller = *Iterator;

		if (Controller && Controller->IsLocalController() && !Controller->IsPrimaryPlayer())
		{
			ULocalPlayer* ExPlayer = Cast<ULocalPlayer>(Controller->Player);
			if (ExPlayer)
			{
				PlayersToRemove[iRemIndex++] = ExPlayer;

				Controller->PawnPendingDestroy(Controller->GetPawn());
			}
		}
	}

	for (int i = 0; i < iRemIndex; ++i)
	{
		GetGameInstance()->RemoveLocalPlayer(PlayersToRemove[i]);
	}
}

void ATankPlayerController::OnDeath()
{
	TankDeath();

	ATank* CurTank = Cast<ATank>(GetPawn());

	CurTank->SpawnDeathParticle();

	GetPawn()->Destroy();
	
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
