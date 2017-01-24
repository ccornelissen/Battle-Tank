// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "TankSpawner.h"



// Sets default values
ATankSpawner::ATankSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ATankSpawner::Initialize(int32 iBotNum, bool bPlayerTeam, bool bTwoPlay)
{
	iNumberOfBots = iBotNum;
	bPlayerSameTeam = bPlayerTeam;
	bTwoPlayers = bTwoPlay;
}

void ATankSpawner::AddPlayerTwo()
{
	//Get spawn location
	FVector SpawnLoc = SpawnerArray[1]->GetActorLocation();
	FRotator SpawnRot = SpawnerArray[1]->GetActorRotation();

	//Spawn the controlled tank
	ATank* PlayerTwoTank = GetWorld()->SpawnActor<ATank>(TankBlueprint, SpawnLoc, SpawnRot);

	//Create the player
	ATankPlayerController* PlayerTwoController = Cast<ATankPlayerController>(UGameplayStatics::CreatePlayer(GetWorld(), -1, true));

	//If controlled is not null possess the spawned tank
	if (PlayerTwoController)
	{
		PlayerTwoController->Possess(PlayerTwoTank);

		//Adjust the players aiming for the bottom screen
		PlayerTwoController->SetViewportAdjust(2.0f);

		ATankPlayerController* PlayerOne = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());

		//Adjusting players aiming for the top screen
		PlayerOne->SetViewportAdjust(0.5f);
	}
	
	
}

void ATankSpawner::Spawner()
{
}

// Called when the game starts or when spawned
void ATankSpawner::BeginPlay()
{
	Super::BeginPlay();

	//if (bTwoPlayers)
	//{
		//Add player two if the player set the bool true in the settings
		AddPlayerTwo();
	//}
}

