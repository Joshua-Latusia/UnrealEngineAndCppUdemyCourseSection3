// Copyright Joshua Latusia 2018

#pragma once

#include "CoreMinimal.h"
#include "engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	void OpenDoor();
	void CloseDoor();
	AActor* Door = nullptr;
	FRotator Rotation;
	const float OPENDOOR_TRIGGER_MASS = 50.f;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(VisibleAnywhere)
	float CurrentAngle = 0.0f;

	// Angle of opening door anticlockwise
	UPROPERTY(VisibleAnywhere)
	float OpenDoorAntiClockWiseAngle = -90.0f;

	// Angle of opening door clockwise
	UPROPERTY(VisibleAnywhere)
	float OpenDoorClockWiseAngle = 90.0f;

	// Amount of  Weight needed to open the door
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpensDoor = nullptr;

	// Amount of seconds before door when trigger is not triggered anymore
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.5f;

	// Save time of when door must close
	float DoorOpenedTime = 0.0f;
	
	/// <summary>
	/// Gets the mass on the trigger volume in kg.
	/// </summary>
	/// <returns></returns>
	float GetMassOnTriggerVolume();
};
