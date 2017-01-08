// Property of Cody Cornelissen.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;
class UTankTurret;
class ATankProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	//Function to set all tank references, called in blueprint
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* Barrel, UTankTurret* Turret, UTankAimingComponent* AimComponent);

	//Reference to the tanks aiming component
	UPROPERTY(BlueprintReadOnly, Category = "Tank Part")
	UTankAimingComponent* TankAimingComponent = nullptr;

	//Firest the tank
	UFUNCTION(BlueprintCallable, Category = "Tank")
	void Fire();

	//Variable used to set and update reloading UI
	UFUNCTION(BlueprintCallable, Category = "Firing")
	float GetReloadTracker() const;

	//Tank's forward launch force, used to propel the tank
	UPROPERTY(EditAnywhere, Category = "Firing")
	float fLaunchSpeed = 4500.0f;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComp) override;

	//Float that handles how often the tank can shoot
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float fTankReloadTimer = 3.0f;

	//Reference to the tanks fired projectile setup in the blueprint
	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<ATankProjectile> ProjectileBlueprint;

	//Pointer references to tank components
	UTankTurret* TankTurret = nullptr;
	UTankBarrel* TankBarrel = nullptr;

	//Float to track the last time the tank fired
	float fLastFireTime = 0.0;
};
