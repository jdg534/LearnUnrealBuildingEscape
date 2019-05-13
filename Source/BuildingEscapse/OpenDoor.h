// (learning unreal)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"

#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpen);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClose);


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
	FOnOpen OnOpen;

	UPROPERTY(BlueprintAssignable)
	FOnClose OnClose;

private:
	const float GetNetMassOnTriggerPlate(); // note return value in kg

	AActor* m_owner;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* DoorOpenTriggerVolume = nullptr;
	
	UPROPERTY(EditAnywhere)
	float RequiredMassToOpen = 50.0f;	
};
