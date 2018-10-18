// Copyright Joshua Latusia 2018

#include "Grabber.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Core/Public/Math/Color.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

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
	Name = GetOwner()->GetName();

	InitPhysicsHandle();
	InitInputComponent();
	
}

void UGrabber::InitPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : PhysicsHandleComponent could not be found"), *Name);
	}
}

void UGrabber::InitInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s : InputComponent could not be found"), *Name);
	}
}

// Called when right mouse button is pressed
void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("%s : Grabbing item"), *Name);

	// Start Linetrace and see if there is collisions
	auto HitResult = GetFirstPhysicsBodyInReach();
	const auto ComponentToGrab = HitResult.GetComponent();
	const auto ActorHit = HitResult.GetActor();

	// On hit -> attach physics handel
	if(ActorHit)
	{
		if(PhysicsHandle)
		{
			PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), FRotator::ZeroRotator);
		}
	}
}

// Calleed when right mouse button is released
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("%s : Releasing item"), *Name);
	if(PhysicsHandle)
	{
		PhysicsHandle->ReleaseComponent();
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If handle is attached, move component
	if(PhysicsHandle && PhysicsHandle->GrabbedComponent)
	{
		UpdateLineTraceEnd();
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	UpdateLineTraceEnd();

	// Setup query params
	const FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	// Line-trace 
	FHitResult HitResult;
	const bool HitObject = GetWorld()->LineTraceSingleByObjectType(OUT HitResult, PlayerLocation, LineTraceEnd, FCollisionObjectQueryParams(ECC_PhysicsBody), TraceParameters);
	if (HitObject)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber hit the object : %s"), *HitResult.Actor->GetName());
	}
	return HitResult;
}

void UGrabber::UpdateLineTraceEnd()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);
	LineTraceEnd = PlayerLocation + PlayerRotation.Vector() * GrabReach;
}

