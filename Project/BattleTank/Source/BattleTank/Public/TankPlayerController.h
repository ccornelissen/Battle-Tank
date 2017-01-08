// Property of Cody Cornelissen.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 *  Controls the players interactions with the tank and aiming component
 */

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

protected:
	//Function that tells the UI when it is safe to set its components
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingComponent);

	UTankAimingComponent* AimComp = nullptr;

private:
	//Start the tank moving the barrel so that projectile will fly towards the cross hair
	void AimTowardsCrosshair();

	//Returns the location of the ray cast if true
	bool GetSightRayHitLocation(FVector& Vector);

	//Returns the look direction based off of the screen space location if true
	bool GetLookDirection(FVector& LookVector) const;

	UPROPERTY(EditDefaultsOnly)
	float fCrossHairXLocation = 0.5f, fCrossHairYLocation = 0.33333f;
	
	UPROPERTY(EditDefaultsOnly)
	float fLineTraceRange = 1000000.0f;
};
