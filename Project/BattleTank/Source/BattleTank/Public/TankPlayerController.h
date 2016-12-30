// Property of Cody Cornelissen.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ATank* GetControlledTank() const;
	
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

private:
	//Start the tank moving the barrel so that projectile will fly towards the cross hair
	void AimTowardsCrosshair();
	
};
