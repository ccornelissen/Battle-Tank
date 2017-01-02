// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "TankProjectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

void ATank::SetBarrelReference(UTankBarrel* Barrel)
{
	TankBarrel = Barrel;
	TankAimingComponent->SetBarrelReference(Barrel);
}

void  ATank::SetTurretReference(UTankTurret* Turret)
{
	TankAimingComponent->SetTurretReference(Turret);
}

void ATank::Fire()
{
	if (TankBarrel == nullptr)
	{
		return;
	}
	
	FVector SpawnLoc = TankBarrel->GetSocketLocation(FName("ProjectileLocation"));
	FRotator SpawnRot = TankBarrel->GetSocketRotation(FName("ProjectileLocation"));

	if (ProjectileBlueprint == nullptr)
	{
		return;
	}

	ATankProjectile* CurProjectile = GetWorld()->SpawnActor<ATankProjectile>(ProjectileBlueprint, SpawnLoc, SpawnRot);

	CurProjectile->LaunchProjectile(fLaunchSpeed);

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

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimingAt(HitLocation, fLaunchSpeed);
}