// Property of Cody Cornelissen.

#pragma once

#include "GameFramework/Actor.h"
#include "AmmoBox.generated.h"

UCLASS()
class BATTLETANK_API AAmmoBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoBox();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	float fTimer;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float fRotationSpeed = 25.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float fRespawnTimer = 30.0f;
};
