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
	AActor* Door;
	FRotator Rotation;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	// Angle of an opened door
	UPROPERTY(VisibleAnywhere)
	float OpenDoorAngle = 85.0f;

	// Amounth of  Weight needed to open the door
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;
	
};
