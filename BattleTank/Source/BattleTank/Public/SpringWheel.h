// Copyright Red Wagon

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"
#include "SpringWheel.generated.h"

UCLASS()
class BATTLETANK_API ASpringWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpringWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float force);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SetupConstraints();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ApplyForce();

	// components
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UPhysicsConstraintComponent * MassConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UPhysicsConstraintComponent * AxleConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	USphereComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	USphereComponent* Axle = nullptr;

	float TotalForceMagnitudeThisFrame = 0;
};
