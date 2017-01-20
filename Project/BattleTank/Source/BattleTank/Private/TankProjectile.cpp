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

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

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

//On hit function called when the projectile collides with another object
void ATankProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//Deactivate the launch particles
	LaunchBlast->Deactivate();
	
	//Apply the explosion force
	ExplosionForce->FireImpulse();

	//Activate the impact blast
	ImpactBlast->Activate();

	//Set ImpactBlast as the root component (so we can destroy collision safely)
	SetRootComponent(ImpactBlast);

	//Destroy the collision mesh
	CollisionMesh->DestroyComponent(false);

	//Apply damage to the enemy tank. 
	UGameplayStatics::ApplyRadialDamage(
		this, 
		fProjectileDamage, //Set on blueprint
		GetActorLocation(), 
		ExplosionForce->Radius, //Takes the radius from the explosion force 
		UDamageType::StaticClass(), 
		TArray<AActor*>() //Empty array as there are no actors we want to ignore
	);

	//Set a timer to destroy the projectile
	FTimerHandle ProjectileHandle;
	GetWorld()->GetTimerManager().SetTimer(ProjectileHandle, this, &ATankProjectile::OnTimerExpire, fLifeSpan);
}

void ATankProjectile::OnTimerExpire()
{
	Destroy();
}

//When the projectile is spawned and fired from the tank. 
void ATankProjectile::LaunchProjectile(float fFireSpeed)
{
	//Active the movement component
	ProjectileMovement->Activate();
	
	//Apply the fire force to the projectile. 
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * fFireSpeed);
}

