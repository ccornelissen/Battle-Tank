// Property of Cody Cornelissen.

#pragma once

#include "GameFramework/Actor.h"
#include "TankProjectile.generated.h"

UCLASS()
class BATTLETANK_API ATankProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATankProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LaunchProjectile(float fFireSpeed);

private:
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* ExplosionForce = nullptr;

	//Length of time before the projectile is destoryed. Want this to match up with Impact particle length.
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float fLifeSpan = 5.0f;

	//Amount of damage the projectile deals to the hit target.
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float fProjectileDamage = 20.0f;

	void OnTimerExpire();

	bool bLifeTimer = false;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
};
