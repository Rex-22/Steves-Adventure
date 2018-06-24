#include "OpenDoor.h"

UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	if (!pressurePlate) { UE_LOG(LogTemp, Error, TEXT("No Presure Plate set")) }
	owner = GetOwner();
}

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActorOnPlates() > triggerMass)
	{
		onOpenRequest.Broadcast();
	}
	else {
		onCloseRequest.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOfActorOnPlates() {
	float totalMass = 0.0f;

	TArray<AActor*> overlappingActors;
	if (!pressurePlate) { return 0.0f; }
	pressurePlate->GetOverlappingActors(overlappingActors);

	for (const auto* actor : overlappingActors) {
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return totalMass;
}
