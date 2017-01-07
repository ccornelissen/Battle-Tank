// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Tank.h"
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
	if (Barrel == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Barrel to set on Aiming Component"));
		return;
	}

	TankBarrel = Barrel;

	if (Turret == nullptr)
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

void UTankAimingComponent::AimingAt(FVector HitLocation, float fFireVelocity)
{
	if (TankBarrel == nullptr)
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

void UTankAimingComponent::SetAimingState(FHitResult Hit)
{
	if (Hit.Actor != nullptr)
	{
		ATank* Tank = Cast<ATank>(Hit.GetActor());

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

void UTankAimingComponent::MoveBarrel(FVector AimAt)
{
	//Calculate where the barrel has to move based on target.
	FRotator BarrelRotation = TankBarrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimAt.Rotation();

	FRotator RotationDifference = AimAsRotator - BarrelRotation;

	//Move tankbarrel to face the direction.
	TankBarrel->ElevateBarrel(RotationDifference.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector AimAt)
{
	FRotator TurretRotation = TankTurret->GetForwardVector().Rotation();
	FRotator AimAtRotation = AimAt.Rotation();

	FVector RotationDifference = AimAtRotation.Euler() - TurretRotation.Euler();

	//Move the turret
	TankTurret->MoveTurret(RotationDifference.Z);
}
