// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* Barrel)
{
	TankBarrel = Barrel;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTankAimingComponent::AimingAt(FVector HitLocation, float fFireVelocity)
{
	if (TankBarrel == nullptr)
	{
		return;
	}

	FVector LaunchVelocity;
	FVector StartLocation = TankBarrel->GetSocketLocation(FName("ProjectileLocation"));

	//Calculate the out launch velocity 
	if (UGameplayStatics::SuggestProjectileVelocity 	//Get the aim direction
		(
			this,
			LaunchVelocity,
			StartLocation,
			HitLocation,
			fFireVelocity,
			false,
			0.0f,
			0.0f,
			ESuggestProjVelocityTraceOption::DoNotTrace
			)
		)
	{
		FVector AimDirection = LaunchVelocity.GetSafeNormal();

		FVector BarrelLocation = TankBarrel->GetComponentLocation();

		UE_LOG(LogTemp, Warning, TEXT("%s is the aimdirection"), *AimDirection.ToString());
	}
	
}