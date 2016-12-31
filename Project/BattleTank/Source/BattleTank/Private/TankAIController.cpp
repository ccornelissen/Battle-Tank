// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	if (GetControlledTank() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Controlled tank returning null"), *GetPawn()->GetName())
	}

	if (GetPlayerTank() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Couldn't find the player."), *GetPawn()->GetName())
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank() != nullptr)
	{
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
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
