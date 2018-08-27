// Copyright Red Wagon

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();

	float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// returns current health as percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

private:

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	int32 StartHealth = 100;

	UPROPERTY(VisibleAnywhere, Category="Health")
	int32 CurrentHealth = StartHealth;
};
