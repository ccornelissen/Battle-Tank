// Property of Cody Cornelissen.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Forward declaration
class UTankBarrel;
class ATankProjectile;
class UTankTurret;

UENUM(BlueprintType)
enum class EReticleState : uint8
{
	RS_Aiming UMETA(DisplayName = "Aiming"), //When the tank is aiming at something that is not an enemy
	RS_Locked UMETA(DisplayName = "Locked"), //When the tank is aiming at an enemy
	RS_Empty UMETA(DisplayName = "Out of Ammo") //When the tank is out of shells
};

//Holds tank barrels properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* Barrel, UTankTurret* Turret);

	//Function that aims at the given location
	void AimAt(FVector HitLocation);

	//Firest the tank
	UFUNCTION(BlueprintCallable, Category = "Tank")
	void Fire();

	//Variable used to set and update reloading UI
	UFUNCTION(BlueprintCallable, Category = "Firing")
	float GetReloadTracker() const;

	void SetAimingState(FHitResult Hit);

	//Stored variable that tracks how close the AI turret is to facing the players location
	float fRotationDiff = 0.0f;

	//Return the ammount of ammo the tank has left.
	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundsLeft() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EReticleState ReticleState = EReticleState::RS_Aiming;

private:

	//Reference to tank parts this class controls the movement of
	UTankBarrel* TankBarrel = nullptr;
	UTankTurret* TankTurret = nullptr;

	//Hold the direction we want to move the barrel and turret.
	FVector AimDirection;

	//Force applied to the projectile on launch
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float fLaunchSpeed = 4500.0f;

	//Moving the barrel to aim at the reticle
	void MoveBarrel(FVector AimAt);

	//Rotating the turret to face the same direction the player is looking
	void MoveTurret(FVector AimAt);

	//Float that handles how often the tank can shoot
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float fTankReloadTimer = 3.0f;

	//Amount of ammo the tank has
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 iAmmo = 5;

	//Reference to the tanks fired projectile setup in the blueprint
	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<ATankProjectile> ProjectileBlueprint;

	void AimingAt(FVector HitLocation, float fFireVelocity);

	//Float to track the last time the tank fired
	float fLastFireTime = 0.0;
	
};
