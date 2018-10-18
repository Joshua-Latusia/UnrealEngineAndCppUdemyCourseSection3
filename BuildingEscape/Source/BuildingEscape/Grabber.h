// Copyright Joshua Latusia 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

private:
	
	/// <summary>
	/// The name of the owner
	/// </summary>
	FString Name;

	/// <summary>
	/// The player location
	/// </summary>
	FVector PlayerLocation;
	
	/// <summary>
	/// The player rotation
	/// </summary>
	FRotator PlayerRotation;


	UPROPERTY(EditAnywhere)	
	/// <summary>
	///  Distance the player can reach to grab objects
	/// </summary>
	float GrabReach = 150.f;
	
	/// <summary>
	/// The line trace end
	/// </summary>
	FVector LineTraceEnd;
	
	/// <summary>
	/// Updates the line trace end.
	/// </summary>
	void UpdateLineTraceEnd();

	/// <summary>
	/// The physics handle
	/// </summary>
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	
	/// <summary>
	/// The input component
	/// </summary>
	UInputComponent* InputComponent = nullptr;

	/// <summary>
	/// Grabs item in the ray cast
	/// </summary>
	void Grab();
	
	/// <summary>
	/// Releases item that is grabber.
	/// </summary>
	void Release();
	
	/// <summary>
	/// Initializes the physics handle.
	/// </summary>
	void InitPhysicsHandle();
	
	/// <summary>
	/// Initializes the input component.
	/// </summary>
	void InitInputComponent();
	
	/// <summary>
	/// Gets the first physics body in reach.
	/// </summary>
	/// <returns></returns>
	FHitResult GetFirstPhysicsBodyInReach();
};
