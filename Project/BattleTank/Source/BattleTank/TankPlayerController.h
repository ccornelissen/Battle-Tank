// Property of Cody Cornelissen.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //must be last include 


UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	ATank* GetControlledTank() const;

	void BeginPlay() override;
	
	
};
