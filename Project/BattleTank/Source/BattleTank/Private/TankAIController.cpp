// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankSpawner.h" //To access array of tanks
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

	//Get the spawner from the world
	for (TActorIterator<ATankSpawner> SpawnItr(GetWorld()); SpawnItr; ++SpawnItr)
	{
		//Set array of enemy tanks based off of set team
		if (SpawnItr)
		{
			if (AITeam == EAITeam::AT_Red)
			{
				EnemyTanks = SpawnItr->BlueTeam;
			}
			else
			{
				EnemyTanks = SpawnItr->RedTeam;
			}
		}

		GetNearestTank();
	}

}

void ATankAIController::GetNearestTank()
{
	float NearestDist;

	if (!NearestTank)
	{
		NearestDist = 10000000000000000000.0f;
	}
	else
	{
		FVector CurTankLoc = NearestTank->GetActorLocation();
		FVector OurLoc = GetPawn()->GetActorLocation();

		NearestDist = FVector::Dist(OurLoc, CurTankLoc);
	}

	for (ATank* CurTank : EnemyTanks)
	{
		if (CurTank && GetPawn())
		{
			FVector CurTankLoc = CurTank->GetActorLocation();
			FVector OurLoc = GetPawn()->GetActorLocation();

			float Dist = FVector::Dist(OurLoc, CurTankLoc);

			if (Dist < NearestDist)
			{
				NearestTank = CurTank;
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
	
	if (NearestTank)
	{
		GetNearestTank();
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
				//Pass the hit to the aiming component to update the reticle
				AimingComponent->Fire();

			}
		}
	}
}

void ATankAIController::OnDeath()
{
	if (GetPawn())
	{
		GetPawn()->DetachFromControllerPendingDestroy();
	}
}



