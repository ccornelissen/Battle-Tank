// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = Cast<ATank>(GetPawn());

	if (ControlledTank == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s, does not have a Controlled Tank"), *GetPawn()->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (PlayerTank != nullptr && ControlledTank != nullptr)
	{
		MoveToActor(PlayerTank, fAIFightRadius);

		//Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//Fire if ready
		ControlledTank->Fire();
	}
}



