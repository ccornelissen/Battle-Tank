// Property of Cody Cornelissen.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	//Returns current health as a percentage
	UFUNCTION(BlueprintPure, Category = "Health")
	float fGetHealthPercent() const; 

	//Delegate that broadcasts to the controller when the tank dies
	FOnDeath OnDeath;

	//Set color based on team
	void SetTeamColor(UMaterialInterface* Color);

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComp) override;

	//Called by the engine when the tank takes damage.
	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	//The amount of health the tanks have
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 iTankHealth = 100;

	////Mesh references that have their color changed based on team 
	//UPROPERTY(EditDefaultsOnly, Category = "Tank Parts")
	//UStaticMeshComponent* BodyMesh = nullptr;

	//UPROPERTY(EditDefaultsOnly, Category = "Tank Parts")
	//UStaticMeshComponent* TurretMesh = nullptr;

	//UPROPERTY(EditDefaultsOnly, Category = "Tank Parts")
	//UStaticMeshComponent* BarrelMesh = nullptr;

	int32 iCurrentHealth;
};

