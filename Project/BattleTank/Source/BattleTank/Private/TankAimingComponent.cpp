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

//Initialize references to tank components, this is done in the Tank blueprint
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

	iCurrentAmmo = iMaxAmmo;
}

//Sets the turret to aim at the hit location
void UTankAimingComponent::AimAt(FVector HitLocation)
{
	//Passing the hit location and tank launch spped to the tank aiming component for firing the projectile
	AimingAt(HitLocation, fLaunchSpeed);
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
		AimDirection = HitLocation.GetSafeNormal(); //TODO make this return a better number so the barrel doesn't go "limp"
	}

	MoveBarrel(AimDirection);
	MoveTurret(AimDirection);
}

//Fires the projectile from the gun
void UTankAimingComponent::Fire()
{
	//TODO make the state machine control the firing 
	//Setting a bool based on if the player has reloaded
	bool bIsReloaded = (GetWorld()->GetTimeSeconds() - fLastFireTime) > fTankReloadTimer;

	//Checking the barrel and reload bool
	if (ensure(TankBarrel) && bIsReloaded && iCurrentAmmo != 0)
	{
		//Creating projectile spawn variables
		FVector SpawnLoc = TankBarrel->GetSocketLocation(FName("ProjectileLocation"));
		FRotator SpawnRot = TankBarrel->GetSocketRotation(FName("ProjectileLocation"));

		if (ensure(ProjectileBlueprint))
		{
			//Spawn the projectile
			ATankProjectile* CurProjectile = GetWorld()->SpawnActor<ATankProjectile>(ProjectileBlueprint, SpawnLoc, SpawnRot);

			//Launch the projectile using set speed
			CurProjectile->LaunchProjectile(fLaunchSpeed);
		}

		//Take away an ammo
		iCurrentAmmo--;

		//Set the reload timer
		fLastFireTime = GetWorld()->GetTimeSeconds();
	}
}

//Used to update the reload UI progress bar
float UTankAimingComponent::GetReloadTracker() const
{
	return GetWorld()->GetTimeSeconds() - fLastFireTime;
}

//Returns the ammount of ammo the tank has, currently used to update the UI
int UTankAimingComponent::GetRoundsLeft() const
{
	return iCurrentAmmo;
}


//Function to control the reticle color, based off of what the player is aiming at
void UTankAimingComponent::SetAimingState(FHitResult Hit)
{
	if (iCurrentAmmo == 0)
	{
		ReticleState = EReticleState::RS_Empty;
		return;
	}

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

	FRotator RotationDifference = AimAtRotation - TurretRotation;

	//Storing as public variable so the AI knows when it is aiming towards the player and can fire. 
	fRotationDiff = RotationDifference.Yaw;

	//Check to make sure the turret rotates the shortest distance. 
	if (FMath::Abs(RotationDifference.Yaw) < 190.0f)
	{
		//Move the turret
		TankTurret->MoveTurret(RotationDifference.Yaw);
	}
	else
	{
		TankTurret->MoveTurret(-RotationDifference.Yaw);
	}
	
}
