// Copyright Joshua Latusia 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	/// <summary>
	/// The player location
	/// </summary>
	FVector PlayerLocation;
	
	/// <summary>
	/// The player rotation
	/// </summary>
	FRotator PlayerRotation;

	// Distance the player can reach to grab objects
	UPROPERTY(EditAnywhere)
	float GrabReach = 150.f;
		
};
