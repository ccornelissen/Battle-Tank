// Property of Cody Cornelissen.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Tank)
	void SetThrottle(float Throttle);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float fMaxUnitsPerSecond = 450000.0f; //Mass times desired acceleration (45000kg * 10m/s)

private:
	UTankTrack();

	void ApplySidewaysForce();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	float fCurrentThrottle = 0.0f;
	void DriveTracks();
};
