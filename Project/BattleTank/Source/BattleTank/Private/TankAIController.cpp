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

	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (PlayerTank)
	{
		MoveToActor(PlayerTank, fAIFightRadius);

		//Get player location
		FVector PlayerLoc = PlayerTank->GetActorLocation();
		if (AimingComponent)
		{
			//Aim towards the player
			AimingComponent->AimAt(PlayerLoc);

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



