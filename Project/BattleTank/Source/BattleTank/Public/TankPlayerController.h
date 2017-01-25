// Property of Cody Cornelissen.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathEvent); //To trigger events in blueprint on death 

//Controls the owning team of the tank
UENUM()
enum class EPlayerTeam : uint8
{
	PT_Blue,
	PT_Red
};

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

	void SetViewportAdjust(float Viewport);

	EPlayerTeam PlayerTeam = EPlayerTeam::PT_Blue;

protected:
	//Function that tells the UI when it is safe to set its components
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingComponent);

	//Event to tell blueprint the user has died
	UFUNCTION(BlueprintImplementableEvent, Category = "Death")
	void TankDeath(FVector Location, FRotator Rotation); 

	UTankAimingComponent* AimComp = nullptr;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UParticleSystemComponent* DeathExplosion = nullptr;

	//Overriding to set up delegate when pawn get controlled
	virtual void SetPawn(APawn* InPawn) override;

	//Function called on death
	UFUNCTION()
	void OnDeath();

	//Adjust viewport in the case of split screen
	float fViewportAdjust = 1.0f;

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
