// Copyright Red Wagon

#include "SpringWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASpringWheel::ASpringWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Mass Constraint"));
	SetRootComponent(MassConstraint);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ASpringWheel::BeginPlay()
{
	Super::BeginPlay();
	SetupConstraints();
}

void ASpringWheel::SetupConstraints()
{
	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	MassConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Cast<UPrimitiveComponent>(Wheel), NAME_None);
}

// Called every frame
void ASpringWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

