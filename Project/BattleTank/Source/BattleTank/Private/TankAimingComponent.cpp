// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankProjectile.h"
#include "TankAimingComponent.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::Initialize(UTankBarrel* Barrel, UTankTurret* Turret)
{
	if (!ensure(Barrel))
	{
		UE_LOG(LogTemp, Error, TEXT("No Barrel to set on Aiming Component"));
		return;
	}

	TankBarrel = Barrel;

	if (!ensure(Turret))
	{
		UE_LOG(LogTemp, Error, TEXT("No Turret to set on Aiming Component"));
		return;
	}

	TankTurret = Turret;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

//Function to find where the user is aiming, gets the vector that is used to control turret and barrel
void UTankAimingComponent::AimingAt(FVector HitLocation, float fFireVelocity)
{
	if (!ensure(TankBarrel))
	{
		return;
	}
	
	FVector LaunchVelocity;
	FVector StartLocation = TankBarrel->GetSocketLocation(FName("ProjectileLocation"));

	//Get the aim direction
	bool bAdjustAim = UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, StartLocation, HitLocation, fFireVelocity, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);

	//Calculate the out launch velocity 
	if (bAdjustAim)
	{
		AimDirection = LaunchVelocity.GetSafeNormal();
	}
	else
	{
		AimDirection = HitLocation.GetSafeNormal();
	}

	MoveBarrel(AimDirection);
	MoveTurret(AimDirection);
}

//Fires the projectile from the gun
void UTankAimingComponent::Fire()
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

//Used to update the reload UI progress bar
float UTankAimingComponent::GetReloadTracker() const
{
	return GetWorld()->GetTimeSeconds() - fLastFireTime;
}

//Function to control the reticle color, based off of what the player is aiming at
void UTankAimingComponent::SetAimingState(FHitResult Hit)
{
	if (Hit.Actor != nullptr)
	{
		APawn* Tank = Cast<APawn>(Hit.GetActor());

		if (Tank != nullptr)
		{
			ReticleState = EReticleState::RS_Locked;
		}
		else
		{
			ReticleState = EReticleState::RS_Aiming;
		}
	}
	else
	{
		ReticleState = EReticleState::RS_Aiming;
	}

}

//Sets the turret to aim at the hit location
void UTankAimingComponent::AimAt(FVector HitLocation)
{
	//Passing the hit location and tank launch spped to the tank aiming component for firing the projectile
	AimingAt(HitLocation, fLaunchSpeed);
}

//Move the tank barrel up and down to match the reticle
void UTankAimingComponent::MoveBarrel(FVector AimAt)
{
	if (!ensure(TankBarrel))
	{
		return;
	}

	//Calculate where the barrel has to move based on target.
	FRotator BarrelRotation = TankBarrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimAt.Rotation();

	FRotator RotationDifference = AimAsRotator - BarrelRotation;

	//Move tankbarrel to face the direction.
	TankBarrel->ElevateBarrel(RotationDifference.Pitch);
}

//Rotate the tank turret to face the aiming reticle
void UTankAimingComponent::MoveTurret(FVector AimAt)
{
	if (!ensure(TankTurret))
	{
		return;
	}

	FRotator TurretRotation = TankTurret->GetForwardVector().Rotation();
	FRotator AimAtRotation = AimAt.Rotation();

	FVector RotationDifference = AimAtRotation.Euler() - TurretRotation.Euler();

	//Move the turret
	TankTurret->MoveTurret(RotationDifference.Z);
}
