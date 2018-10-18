// Copyright Joshua Latusia 2018
#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Math/Rotator.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

/// <summary>
/// Opens the door by adjusting yawn rotation.
/// </summary>
void UOpenDoor::OpenDoor()
{
	if (CurrentAngle > OpenDoorAntiClockWiseAngle)
	{
		CurrentAngle--;
		Door->SetActorRotation(FRotator(0.0f, CurrentAngle, 0.0f));
	}
}

/// <summary>
/// Closes the door.
/// </summary>
void UOpenDoor::CloseDoor()
{
	if (CurrentAngle < 0.0f && DoorOpenedTime + DoorCloseDelay < GetWorld()->GetTimeSeconds())
	{
		CurrentAngle++;
		Door->SetActorRotation(FRotator(0.0f, CurrentAngle, 0.0f));
	}
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Door = GetOwner();

}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetMassOnTriggerVolume() > OPENDOOR_TRIGGER_MASS)
	{
		OpenDoor();
		DoorOpenedTime = GetWorld()->GetTimeSeconds();
	}
	else
	{
		CloseDoor();
	}
}

float UOpenDoor::GetMassOnTriggerVolume()
{
	float totalMass = 0.f;
	// Find all overlapping actors on pressure plate and calcultae mass
	TArray<AActor*> overlappingActors;
	PressurePlate->GetOverlappingActors(overlappingActors);

	for(const auto& actor : overlappingActors)
	{
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Error, TEXT("%s : Is standing in the triggervolume"), *actor->GetName());
	}

	return totalMass;
}

