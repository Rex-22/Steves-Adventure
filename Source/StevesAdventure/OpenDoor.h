#pragma once

#include "CoreMinimal.h"

#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"

#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEVESADVENTURE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float openAngle = -60.0f;

	UPROPERTY(EditAnywhere)
		float triggerMass = 30.0f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* pressurePlate;

	UPROPERTY(EditAnywhere)
		float doorCloseDelay = 0.4f;
	
	AActor* owner;
	float lastDoorOpenTime;

public:	
	UOpenDoor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor();
	void CloseDoor();
private:
	float GetTotalMassOfActorOnPlates();
	
};
