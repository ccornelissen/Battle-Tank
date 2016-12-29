// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	if (GetControlledTank() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is being controlled by AI."), *GetControlledTank()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled tank returning null"))
	}

	if (GetPlayerTank() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found the player: %s"), *GetPlayerTank()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't find the player."))
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APawn* PlayerPawn = nullptr;

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (PlayerPawn != nullptr)
	{
		return Cast<ATank>(PlayerPawn);
	}

	return nullptr;
}
