// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "AmmoBox.h"


// Sets default values
AAmmoBox::AAmmoBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->bGenerateOverlapEvents = true;
	CollisionMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionMesh->SetCanEverAffectNavigation(false);
}

// Called when the game starts or when spawned
void AAmmoBox::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnOverlapBegin);
	
}

// Called every frame
void AAmmoBox::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FRotator CurrentRot = CollisionMesh->GetComponentRotation();

	CurrentRot.Yaw += fRotationSpeed * GetWorld()->GetDeltaSeconds();

	CollisionMesh->SetRelativeRotation(CurrentRot);

	fTimer -= GetWorld()->GetDeltaSeconds();

	if (fTimer <= 0.0f)
	{
		CollisionMesh->SetVisibility(true);

		CollisionMesh->bGenerateOverlapEvents = true;
	}

}

void AAmmoBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UTankAimingComponent* TankAimingComp = OtherActor->FindComponentByClass<UTankAimingComponent>();

	if (!TankAimingComp)
	{
		return;
	}

	if (TankAimingComp->iCurrentAmmo != TankAimingComp->iMaxAmmo)
	{
		TankAimingComp->iCurrentAmmo = TankAimingComp->iMaxAmmo;

		CollisionMesh->ToggleVisibility();

		CollisionMesh->bGenerateOverlapEvents = false;

		fTimer = fRespawnTimer;
	}
	
}

