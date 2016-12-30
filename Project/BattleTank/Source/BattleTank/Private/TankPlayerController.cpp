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

	UE_LOG(LogTemp, Warning, TEXT("%s is ticking!"), *GetControlledTank()->GetName());
	//Aim towards crosshair
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (GetControlledTank == nullptr)
	{
		return;
	}

	//Get world locations through line trace
	// If it hits the landscape
		//Tell controlled tank to aim towards cross hair.
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
