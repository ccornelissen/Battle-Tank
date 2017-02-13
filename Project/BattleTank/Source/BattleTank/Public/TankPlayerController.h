// Property of Cody Cornelissen.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathEvent); //To trigger events in blueprint on death 

//Controls the owning team of the tank
UENUM(BlueprintType)
enum class EPlayerTeam : uint8
{
	PT_Blue UMETA(DisplayName = "Blue"),
	PT_Red UMETA(DisplayName = "Red")
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

	UPROPERTY(BlueprintReadOnly, Category = "Team")
	EPlayerTeam PlayerTeam = EPlayerTeam::PT_Blue;

	//Returns the amount of tanks on the red team
	UFUNCTION(BlueprintCallable, Category = "Team")
	int32 RedTeamNumber();

	//Returns the amount of tanks on the blue team
	UFUNCTION(BlueprintCallable, Category = "Team")
	int32 BlueTeamNumber();

protected:
	//Function that tells the UI when it is safe to set its components
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingComponent);
	
	//Used to remove second player before returning to the main menu
	UFUNCTION(BlueprintCallable, Category = "Clean Up")
	void RemovePlayerTwo();

	//Event to tell blueprint the user has died
	UFUNCTION(BlueprintImplementableEvent, Category = "Death")
	void TankDeath(); 

	UTankAimingComponent* AimComp = nullptr;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UParticleSystemComponent* DeathExplosion = nullptr;

	//Hold team arrays for UI
	TArray<ATank*> RedTeam;
	TArray<ATank*> BlueTeam;

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
