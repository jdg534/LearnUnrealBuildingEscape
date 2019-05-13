// (learning unreal)

#include "DoorController.h"
#include "Gameframework/Actor.h"

// Sets default values for this component's properties
UDoorController::UDoorController()
	: m_owner(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDoorController::BeginPlay()
{
	Super::BeginPlay();
	m_owner = GetOwner();
	FString ownerName = m_owner->GetName();
	UE_LOG(LogTemp, Warning, TEXT("UOpenDoor::BeginPlay() called on %s"), *ownerName);

	if(DoorOpenTriggerVolume)
	{
		const FString triggerVolumeName = DoorOpenTriggerVolume->GetName();
		UE_LOG(LogTemp, Log, TEXT("UOpenDoor %s has trigger volume %s associated"), *ownerName, *triggerVolumeName);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UOpenDoor %s needs a trigger volume and Actor to open for"), *ownerName);
	}

}


// Called every frame
void UDoorController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const float massOnTriggerVolume = GetNetMassOnTriggerPlate();

	if (massOnTriggerVolume >= RequiredMassToOpen)
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}

}

const float UDoorController::GetNetMassOnTriggerPlate()
{
	if (DoorOpenTriggerVolume == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s's OpenDoor::GetNetMassOnTriggerPlate() can't run due to lack of a trigger volume"), *GetOwner()->GetName());
	}

	// query the plate trigger volume for all actors, sum mass and return
	float netMass = 0.0f;
	TArray<AActor*> l_overlappingActors;
	DoorOpenTriggerVolume->GetOverlappingActors(l_overlappingActors); // could 

	for (const auto& actorRef : l_overlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("UOpenDoor::GetNetMassOnTriggerPlate() picked up %s"), *actorRef->GetName());
		netMass += actorRef->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return netMass;
}