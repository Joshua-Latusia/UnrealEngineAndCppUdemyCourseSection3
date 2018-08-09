// Copyright Joshua Latusia 2018
#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Math/Rotator.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Door = GetOwner();

	// Get current rotation
	FRotator Rotation = Door->GetActorRotation();
	FString RotationBefore = Rotation.ToString();
	UE_LOG(LogTemp, Error, TEXT("Rotation before : %s"), *RotationBefore);

	// Set Yanw rotation to 90 degrees so door appears open
	FRotator NewRotation = FRotator(0.0f, -60.0f, 0.0f);
	Door->SetActorRotation(NewRotation);
	FString RotationAfter = Door->GetActorRotation().ToString();
	UE_LOG(LogTemp, Error, TEXT("Rotation after : %s"), *RotationAfter);

	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

