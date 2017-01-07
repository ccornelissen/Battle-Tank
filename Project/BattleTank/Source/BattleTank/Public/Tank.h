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

	//Used to set tanks barrel reference
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBarrelReference(UTankBarrel* Barrel);

	//Used to set tanks turret referernce
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetTurretReference(UTankTurret* Turret);

	//Firest the tank
	UFUNCTION(BlueprintCallable, Category = "Tank")
	void Fire();

	//Variable used to set and update reloading UI
	UFUNCTION(BlueprintCallable, Category = "Firing")
	float GetReloadTracker() const;

	UPROPERTY(EditAnywhere, Category = Firing)
	float fLaunchSpeed = 4500.0f;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Tank Part")
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Float that handles how often the tank can shoot
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float fTankReloadTimer = 3.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<ATankProjectile> ProjectileBlueprint;

	UTankBarrel* TankBarrel = nullptr;

	float fLastFireTime = 0.0;
};
