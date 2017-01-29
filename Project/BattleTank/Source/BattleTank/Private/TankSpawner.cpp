// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "TankAIController.h"
#include "TankSpawner.h"



// Sets default values
ATankSpawner::ATankSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ATankSpawner::Initialize(int32 iBotNum, bool bPlayerTeam, bool bTwoPlay)
{
	//Take in the level settings to set the spawner settings, this is handled in the spawner blueprint
	iNumberOfBots = iBotNum;
	bPlayerSameTeam = bPlayerTeam;
	bTwoPlayers = bTwoPlay;
}

void ATankSpawner::AddPlayerTwo()
{
	//Get spawn location
	FVector SpawnLoc = SpawnerArray[0]->GetActorLocation();
	FRotator SpawnRot = SpawnerArray[0]->GetActorRotation();

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

		//Adjusting players aiming for the top screen
		ATankPlayerController* PlayerOne = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());

		if (PlayerOne)
		{
			PlayerOne->SetViewportAdjust(0.5f);
		}
		
		//If they don't want players on the same team change player twos color and team to red team
		if (bPlayerSameTeam == false)
		{
			PlayerTwoTank->SetTeamColor(RedMaterial);

			PlayerTwoTank->TankTeam = ETankTeam::TT_Red;

			PlayerTwoController->PlayerTeam = EPlayerTeam::PT_Red;

			iRedTeam++;
		}
		else
		{
			iBlueTeam++;
		}
	}
	
	
}

//Change tank color and controller team association
void ATankSpawner::SetTeam(ATank* Tank, ATankAIController* Controller)
{
	if (Tank != nullptr && Controller != nullptr)
	{
		//Check the number of players on each team to ensure they stay equal. 
		if (iBlueTeam <= iRedTeam)
		{
			//Don't need to set team or tank color as blue is the default
			iBlueTeam++;
		}
		else
		{
			Tank->SetTeamColor(RedMaterial);
			iRedTeam++;
			Tank->TankTeam = ETankTeam::TT_Red;
			Controller->AITeam = EAITeam::AT_Red;
		}
	}
}

void ATankSpawner::Spawner()
{
	int32 iCount = 0;

	if (bTwoPlayers)
	{
		//Add player two if the player set the bool true in the settings
		AddPlayerTwo();

		iCount++;
	}

	for (iCount; iCount < iNumberOfBots; iCount++)
	{
		if (SpawnerArray[iCount])
		{
			//Get spawn location
			FVector SpawnLoc = SpawnerArray[iCount]->GetActorLocation();
			FRotator SpawnRot = SpawnerArray[iCount]->GetActorRotation();


			//Spawn AI
			ATankAIController* Bot = GetWorld()->SpawnActor<ATankAIController>(AIControllerBlueprint, SpawnLoc, SpawnRot);

			//Possess body
			if (Bot)
			{
				//Spawn the controlled tank
				ATank* BotTank = GetWorld()->SpawnActor<ATank>(TankBlueprint, SpawnLoc, SpawnRot);

				if (BotTank)
				{
					Bot->Possess(BotTank);

					SetTeam(BotTank, Bot);
				}
			}
		}
	}


}

// Called when the game starts or when spawned
void ATankSpawner::BeginPlay()
{
	Super::BeginPlay();

	//Spawn all the necessary tanks
	Spawner();
}


