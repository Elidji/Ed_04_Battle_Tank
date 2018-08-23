// Copyright Red Wagon

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankAimingComponent.generated.h"

// enum for aiming state
UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Aiming,
	Reloading,
	NoAmmo
};

// Forward Declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds Barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// used to set the barrel and turret
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	// aim the barrel and turret
	void AimAt(FVector HitLocation);

	EFiringStatus GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category="Firing")
	int32 GetAmmoAmt() const;

	// called from blueprints to fire
	UFUNCTION(BlueprintCallable, Category = Actions)
	void Fire();

protected:

	void BeginPlay() override;

	// Used by the player UI blueprint to color the cross hair according to firing state
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:

	// tells the barrel and turret how much to move
	void MoveBarrel();

	bool IsBarrelMoving();

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;
	FVector AimDirection;

	// just allow this change in blueprint, ie default base, not instances
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBP;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 2;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000; // 1000 m/s

	double LastFireTime = 0;  // last time fired in seconds

	int32 AmmoAmount = 3;
};