// Property of Cody Cornelissen.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Forward declaration
class UTankBarrel;
class UTankTurret;

//Holds tank barrels properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* Barrel);
	void SetTurretReference(UTankTurret* Turret);

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void AimingAt(FVector HitLocation, float fFireVelocity);

private:
	UTankBarrel* TankBarrel = nullptr;

	UTankTurret* TankTurret = nullptr;

	//Moving the barrel to aim at the reticle
	void MoveBarrel(FVector AimAt);

	//Rotating the turret to face the same direction the player is looking
	void MoveTurret(FVector AimAt);
	
};
