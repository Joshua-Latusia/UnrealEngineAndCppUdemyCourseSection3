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
	AActor* Door;
	FRotator Rotation;


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

	// Amounth of  Weight needed to open the door
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpensDoor;
};
