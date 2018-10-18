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

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Door = GetOwner();

}

// Called every frame
/// <summary>
/// Ticks the component.
/// </summary>
/// <param name="DeltaTime">The delta time.</param>
/// <param name="TickType">Type of the tick.</param>
/// <param name="ThisTickFunction">The this tick function.</param>
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetMassOnTriggerVolume() > OPENDOOR_TRIGGER_MASS)
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
}

float UOpenDoor::GetMassOnTriggerVolume()
{
	float totalMass = 0.f;
	// Find all overlapping actors on pressure plate and calcultae mass
	TArray<AActor*> overlappingActors;

	if(!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Cant calculte mass on triggervolume, PressurePlate is missing"), *GetOwner()->GetName());
		return totalMass;
	}

	PressurePlate->GetOverlappingActors(overlappingActors);

	for(const auto& actor : overlappingActors)
	{
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Error, TEXT("%s : Is standing in the triggervolume"), *actor->GetName());
	}

	return totalMass;
}

