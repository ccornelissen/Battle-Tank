// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankAimingComponent.h"
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

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (ensure(PlayerTank))
	{
		MoveToActor(PlayerTank, fAIFightRadius);

		//Aim towards the player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		//Fire if ready
		AimingComponent->Fire();
	}
}



