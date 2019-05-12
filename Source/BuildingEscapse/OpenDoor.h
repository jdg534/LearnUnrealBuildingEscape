// (learning unreal)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"

#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPSE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Blueprint events
	UPROPERTY(BlueprintAssignable)
	FOnOpenRequest OnOpenRequest;

private:
	void OpenDoor();
	void CloseDoor();
	const float GetNetMassOnTriggerPlate(); // note return value in kg

	AActor* m_owner;

	UPROPERTY(EditAnywhere)
	float SecondsToCloseDoorAfter;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* DoorOpenTriggerVolume = nullptr;
	
	UPROPERTY(EditAnywhere)
	float RequiredMassToOpen = 50.0f;

	UPROPERTY(VisibleAnywhere)
	float DoorClosedYaw = -10.0f;

	const float c_DoorOpenYaw = -80.0f; // would do this on constructor, unreal build tool complained
	bool m_doorOpen;
	float m_timeOfLastOpenDoor;
};
