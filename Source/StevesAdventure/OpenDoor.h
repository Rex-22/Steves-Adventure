#pragma once

#include "CoreMinimal.h"

#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"

#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEVESADVENTURE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float triggerMass = 30.0f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* pressurePlate;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent onOpenRequest;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent onCloseRequest;
	
	AActor* owner;

public:	
	UOpenDoor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float GetTotalMassOfActorOnPlates();
	
};
