// Property of Cody Cornelissen.

#pragma once

#include "GameFramework/Actor.h"
#include "TankSpawner.generated.h"

class ATank;
class ATankPlayerController;
class ATankAIController;

UCLASS()
class BATTLETANK_API ATankSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATankSpawner();

	//Blueprint callable function that takes in the settings from the main menu. 
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(int32 iBotNum, bool bPlayerTeam, bool bTwoPlay);

private:
	//Spawn a second player if necessary
	void AddPlayerTwo();

	//Set the tank team on the AI tank and controller
	void SetTeam(ATank* Tank, ATankAIController* Controller);

	//Team tracking ints
	int32 iBlueTeam = 1;
	int32 iRedTeam = 0;


	//Create an array the will hold the spawn point locations
	UPROPERTY(EditAnywhere, Category = "Spawn Points")
	TArray<AActor*> SpawnerArray;

	//Blueprint the spawner will spawn
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ATank> TankBlueprint;

	//Blueprint of the player controller 
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ATankPlayerController> PlayerControllerBlueprint;

	//Blueprint of the AI controller 
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ATankAIController> AIControllerBlueprint;

	//Function the loops through the array spawning actors as necessary
	void Spawner();

	//Create a function that will set the team on spawn

	//Materials that are set on the tanks based on team
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UMaterialInterface* RedMaterial;

	//Number of bots to spawn
	int32 iNumberOfBots = 0;

	//Whether or not to spawn the players on the same team
	bool bPlayerSameTeam = false;

	//Whether or not they're playing with 2 people
	bool bTwoPlayers = false;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	
	
};
