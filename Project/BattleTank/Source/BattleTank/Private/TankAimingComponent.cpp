// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* Barrel)
{
	TankBarrel = Barrel;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
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
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, StartLocation, HitLocation, fFireVelocity, ESuggestProjVelocityTraceOption::DoNotTrace);
	//Calculate the out launch velocity 
	if (bHaveAimSolution)
	{
		FVector AimDirection = LaunchVelocity.GetSafeNormal();

		FVector BarrelLocation = TankBarrel->GetComponentLocation();

		MoveBarrel(AimDirection);

		UE_LOG(LogTemp, Warning, TEXT("%s is the aimdirection"), *AimDirection.ToString());
	}
	
}

void UTankAimingComponent::MoveBarrel(FVector AimAt)
{
	//Calculate where the barrel has to move based on target.
	FRotator BarrelRotation = TankBarrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimAt.Rotation();

	FRotator RotationDifference = AimAsRotator - BarrelRotation;

	float fBarrelMoveSpeed = TankBarrel->fMaxDegreesPerSecond;

	//Move tankbarrel to face the direction.
	TankBarrel->ElevateBarrel(fBarrelMoveSpeed);


}
