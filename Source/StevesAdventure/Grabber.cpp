#include "Grabber.h"

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!physicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *(GetOwner()->GetName()));
	}

	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (inputComponent)
	{
		inputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
	}
	else {

		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *(GetOwner()->GetName()));
	}
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (physicsHandle) 
	{
		if (physicsHandle->GetGrabbedComponent()) {
			physicsHandle->SetTargetLocation(GetReachLineEnd());
		}
	}
}

void UGrabber::Grab() 
{
	auto hitResult = GetFirstPhysicsBodyInReach();
	auto componentToGrab = hitResult.GetComponent();
	auto actorHit = hitResult.GetActor();

	if (actorHit) {
		if (componentToGrab)
		{
			if (!physicsHandle) { return; }
			physicsHandle->GrabComponentAtLocationWithRotation(
				componentToGrab, 
				NAME_None, 
				componentToGrab->GetOwner()->GetActorLocation(),
				FRotator(0, 0, 0)
			);
		}
	}
}

void UGrabber::Release()
{
	if (!physicsHandle) { return; }
	physicsHandle->ReleaseComponent();
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
	FHitResult hit;
	FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		hit, 
		GetReachLineStart(), 
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), 
		traceParameters
	);

	return hit;
}

const FVector UGrabber::GetReachLineEnd()
{
	FVector pos;
	FRotator rot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(pos, rot);

	FVector lineTraceEnd = pos + rot.Vector() * reach;
	return lineTraceEnd;
}

const FVector UGrabber::GetReachLineStart()
{
	FVector pos;
	FRotator rot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(pos, rot);
	
	return pos;
}
