// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMoveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Component"));
	ProjectileMoveComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed)
{
	if (!ProjectileMoveComponent) {return;}
	// forward vector is a unit vector
	ProjectileMoveComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMoveComponent->Activate(true);
}