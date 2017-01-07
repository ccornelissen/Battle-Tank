// Property of Cody Cornelissen.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Forward declaration
class UTankBarrel;
class UTankTurret;

UENUM(BlueprintType)
enum class EReticleState : uint8
{
	RS_Aiming UMETA(DisplayName = "Aiming"), //When the tank is aiming at something that is not an enemy
	RS_Locked UMETA(DisplayName = "Locked") //When the tank is aiming at an enemy
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

	// Called when the game starts
	virtual void BeginPlay() override;

	void AimingAt(FVector HitLocation, float fFireVelocity);

	void SetAimingState(FHitResult Hit);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EReticleState ReticleState = EReticleState::RS_Aiming;

private:
	UTankBarrel* TankBarrel = nullptr;

	UTankTurret* TankTurret = nullptr;

	//Hold the direction we want to move the barrel and turret.
	FVector AimDirection;

	//Moving the barrel to aim at the reticle
	void MoveBarrel(FVector AimAt);

	//Rotating the turret to face the same direction the player is looking
	void MoveTurret(FVector AimAt);
	
};
