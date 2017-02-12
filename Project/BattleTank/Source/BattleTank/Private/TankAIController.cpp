// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h" //To implement on death
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(GetPawn()))
	{
		UE_LOG(LogTemp, Error, TEXT("%s, does not have a Controlled Tank"), *GetPawn()->GetName());
	}

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("%s, does not have an aiming component"), *GetPawn()->GetName());
	}

	//Get the nearest tank off start
	GetNearestTank();

}

void ATankAIController::GetNearestTank()
{
	float NearestDist = 0.0f;
	
	if (AITeam == EAITeam::AT_Red) //Look for blue tanks
	{
		iEnemiesRemain = 0;

		for (TActorIterator<ATank> TankItr(GetWorld()); TankItr; ++TankItr)
		{
			//Go through tanks in the world
			if (TankItr && GetPawn())
			{
				if (TankItr->TankTeam == ETankTeam::TT_Blue)
				{
					//Track each enemy on the field
					iEnemiesRemain++;

					FVector CurTankLoc = TankItr->GetActorLocation();
					FVector OurLoc = GetPawn()->GetActorLocation();

					float Dist = FVector::Dist(OurLoc, CurTankLoc);

					//Update nearest tank if the current tank is closer
					if (NearestDist == 0.0f)
					{
						NearestDist = Dist;
						NearestTank = *TankItr;
					}
					else if (Dist < NearestDist)
					{
						NearestDist = Dist;
						NearestTank = *TankItr;
					}
				}
			}
		}
	}
	else //Look for red tanks
	{
		for (TActorIterator<ATank> TankItr(GetWorld()); TankItr; ++TankItr)
		{
			iEnemiesRemain = 0;

			//Go through tanks in the world
			if (TankItr && GetPawn())
			{
				if (TankItr->TankTeam == ETankTeam::TT_Red)
				{
					iEnemiesRemain++;

					FVector CurTankLoc = TankItr->GetActorLocation();
					FVector OurLoc = GetPawn()->GetActorLocation();

					float Dist = FVector::Dist(OurLoc, CurTankLoc);

					if (NearestDist == 0.0f)
					{
						NearestDist = Dist;
						NearestTank = *TankItr;
					}
					else if (Dist < NearestDist)
					{
						NearestDist = Dist;
						NearestTank = *TankItr;
					}

				}
			}
		}
	}

}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		//Get controlled tank
		ATank* PossessedTank = Cast<ATank>(InPawn);

		if (PossessedTank)
		{
			//Attach the On death function to the tanks delegate
			PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnDeath);
		}
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//If no enemies remain stop the tank from trying to act
	if (iEnemiesRemain > 0) 
	{
		GetNearestTank();

		if (NearestTank)
		{
			MoveToActor(NearestTank, fAIFightRadius);

			//Get player location
			FVector TankLoc = NearestTank->GetActorLocation();
			if (AimingComponent)
			{
				//Aim towards the player
				AimingComponent->AimAt(TankLoc);

				//if the barrel is aimed near the player allow AI tank to fire. 
				if (AimingComponent->fRotationDiff < fAIAim)
				{
					//Refilling AI ammo if they're out since they have no knowledge of ammo pick ups.
					if (AimingComponent->iCurrentAmmo == 0)
					{
						AimingComponent->iCurrentAmmo = AimingComponent->iMaxAmmo;
					}

					//Pass the hit to the aiming component to update the reticle
					AimingComponent->Fire();

				}
			}
		}
	}
}

void ATankAIController::OnDeath()
{
	APawn* TankPawn = GetPawn();

	TankPawn->DetachFromControllerPendingDestroy();

	TankPawn->Destroy();

	Destroy();
}



