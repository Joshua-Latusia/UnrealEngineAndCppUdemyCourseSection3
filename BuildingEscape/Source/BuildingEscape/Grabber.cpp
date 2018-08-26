// Copyright Joshua Latusia 2018

#include "Grabber.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Core/Public/Math/Color.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"

// Macro used to mark parameters that get changed by the function
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FString Name = GetOwner()->GetName();
	UE_LOG(LogTemp, Error, TEXT("%s : Grabber is working"), *Name);
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Retrieve player location and rotation
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);

	// Draw trace to see reach of player
	FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector() * GrabReach;
	DrawDebugLine(GetWorld(), PlayerLocation, LineTraceEnd, FColor(0,255,0),false,-1.f,0.f,8.f);

	// Setup query params
	const FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	// Line-trace 
	FHitResult HitResult;
	const bool HitObject = GetWorld()->LineTraceSingleByObjectType(OUT HitResult ,PlayerLocation, LineTraceEnd, FCollisionObjectQueryParams(ECC_PhysicsBody), TraceParameters);
	if(HitObject)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber hit the object : %s"), *HitResult.Actor->GetName());
	}

}

