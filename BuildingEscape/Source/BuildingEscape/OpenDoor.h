// Copyright Joshua Latusia 2018

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	AActor* Door = nullptr;
	const float OPENDOOR_TRIGGER_MASS = 50.f;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	// Amount of  Weight needed to open the door
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;
	
	/// <summary>
	/// Gets the mass on the trigger volume in kg.
	/// </summary>
	/// <returns></returns>
	float GetMassOnTriggerVolume();
};
