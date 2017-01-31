// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	//Set current health equal to blueprint health, If set in contructor or header it does not set correctly
	iCurrentHealth = iTankHealth;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComp)
{
	Super::SetupPlayerInputComponent(InputComp);
}

float ATank::fGetHealthPercent() const
{
	//return current health divided by the maximum possible health to get the percent value
	return (float)iCurrentHealth / (float)iTankHealth;
}

void ATank::SpawnDeathParticle()
{
	if (DeathParticleBlueprint)
	{
		FVector CurLoc = GetActorLocation();
		FRotator CurRot = GetActorRotation();

		AActor* DeathParticle = GetWorld()->SpawnActor<AActor>(DeathParticleBlueprint, CurLoc, CurRot);
	}
}

void ATank::SetTeamColor(UMaterialInterface* Color)
{
	if (Color)
	{
		TArray<UStaticMeshComponent*> StaticMeshArray;

		GetComponents(StaticMeshArray);

		for (UStaticMeshComponent* Mesh : StaticMeshArray)
		{
			Mesh->SetMaterial(0, Color);
		}
	}
}

float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	//Set incoming float to an int. (This is just to keep the numbers nice and round, comparing floats can get ugly)
	int32 iDamagePoints = FPlatformMath::RoundToInt(Damage);

	//Clamp the damage between 0 and our health. 
	int32 iActualDamage = FMath::Clamp<int32>(iDamagePoints, 0, iCurrentHealth);

	//Apply damage
	iCurrentHealth -= iActualDamage;

	//If tank is dead, let it die
	if (iCurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return Damage;
}