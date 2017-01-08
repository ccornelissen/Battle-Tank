// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "TankProjectile.h"
#include "TankMovementComponent.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATank::Initialize(UTankBarrel* Barrel, UTankTurret* Turret, UTankAimingComponent* AimComponent)
{
	if (ensure(Barrel))
	{
		TankBarrel = Barrel;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No reference to the tank barrel on the tank blueprint"));
	}

	if (ensure(Turret))
	{
		TankTurret = Turret;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No reference to the tank turret on the tank blueprint"));
	}

	if (ensure(AimComponent))
	{
		TankAimingComponent = AimComponent;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No reference to the tank aiming component on the tank blueprint"));
	}
}

void ATank::Fire()
{
	bool bIsReloaded = (GetWorld()->GetTimeSeconds() - fLastFireTime) > fTankReloadTimer;

	if (ensure(TankBarrel) && bIsReloaded)
	{
		FVector SpawnLoc = TankBarrel->GetSocketLocation(FName("ProjectileLocation"));
		FRotator SpawnRot = TankBarrel->GetSocketRotation(FName("ProjectileLocation"));

		if (ensure(ProjectileBlueprint))
		{
			ATankProjectile* CurProjectile = GetWorld()->SpawnActor<ATankProjectile>(ProjectileBlueprint, SpawnLoc, SpawnRot);

			CurProjectile->LaunchProjectile(fLaunchSpeed);
		}

		fLastFireTime = GetWorld()->GetTimeSeconds();
	}
}

float ATank::GetReloadTracker() const
{
	return GetWorld()->GetTimeSeconds() - fLastFireTime;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

//Sets the turret to aim at the hit location
void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent))
	{
		return;
	}
	//Passing the hit location and tank launch spped to the tank aiming component for firing the projectile
	TankAimingComponent->AimingAt(HitLocation, fLaunchSpeed);
}