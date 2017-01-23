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

		PlayerTwoController->SetViewportAdjust(0.5f, -0.33333f); //TODO fix player two controllers aiming, it doesn't know where its crosshair is.

		ATankPlayerController* PlayerOne = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());

		PlayerOne->SetViewportAdjust(0.5f, 0.33333f);
	}
	
	
}

void ATankSpawner::Spawner()
{
}

// Called when the game starts or when spawned
void ATankSpawner::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("%i"), bTwoPlayers);

	if (bTwoPlayers)
	{
		AddPlayerTwo();
	}
}


