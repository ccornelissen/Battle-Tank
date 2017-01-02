// Property of Cody Cornelissen.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;
class UTankTurret;
class ATankProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* Barrel);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* Turret);

	UFUNCTION(BlueprintCallable, Category = Tank)
	void Fire();

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float fLaunchSpeed = 4500.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float fTankReloadTimer = 3.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<ATankProjectile> ProjectileBlueprint;

	UTankBarrel* TankBarrel = nullptr;

	

	float fLastFireTime = 0.0;
};
