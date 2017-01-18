// Property of Cody Cornelissen.

#include "BattleTank.h"
#include "TankProjectile.h"


// Sets default values
ATankProjectile::ATankProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create the projectiles collision component
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	//Creating the particle effect that goes off when the projectile is fired
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//Creating the particle that goes off upon the projectile colliding with another object
	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->bAutoActivate = false;
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//Creating the projectile movement component, this propels our projectile through the air
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ATankProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	//Adding the On Hit function to the primitive component
	CollisionMesh->OnComponentHit.AddDynamic(this, &ATankProjectile::OnHit);
}

void ATankProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();

	ImpactBlast->Activate();
}

void ATankProjectile::LaunchProjectile(float fFireSpeed)
{
	ProjectileMovement->Activate();
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * fFireSpeed);
}

