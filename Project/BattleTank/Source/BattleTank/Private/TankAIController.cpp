// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = Cast<ATank>(GetPawn());

	if (!ensure(ControlledTank))
	{
		UE_LOG(LogTemp, Error, TEXT("%s, does not have a Controlled Tank"), *GetPawn()->GetName());
	}

	AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("%s, does not have an aiming component"), *GetPawn()->GetName());
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
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		//Fire if ready
		AimingComponent->Fire();
	}
}



