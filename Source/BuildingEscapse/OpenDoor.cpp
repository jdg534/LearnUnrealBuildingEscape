// (learning unreal)

#include "OpenDoor.h"
#include "Gameframework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
	: m_owner(nullptr)
	, DoorClosedYaw(-10.0f)
	, m_doorOpen(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	m_owner = GetOwner();
	FString ownerName = m_owner->GetName();
	UE_LOG(LogTemp, Warning, TEXT("UOpenDoor::BeginPlay() called on %s"), *ownerName);

	UWorld* world = GetWorld();

	m_timeOfLastOpenDoor = world->GetTimeSeconds();

	if(DoorOpenTriggerVolume)
	{
		const FString triggerVolumeName = DoorOpenTriggerVolume->GetName();
		UE_LOG(LogTemp, Warning, TEXT("UOpenDoor %s has trigger volume %s associated"), *ownerName, *triggerVolumeName);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UOpenDoor %s needs a trigger volume and Actor to open for"), *ownerName);
	}

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// will need an overlap event 

	if (DoorOpenTriggerVolume && GetNetMassOnTriggerPlate() >= RequiredMassToOpen)
	{
		OpenDoor();
	}

	float now = GetWorld()->GetTimeSeconds();
	if (m_doorOpen && now >= (m_timeOfLastOpenDoor + SecondsToCloseDoorAfter))
	{
		CloseDoor();
	}

}

void UOpenDoor::OpenDoor()
{
	OnOpenRequest.Broadcast();
}

void UOpenDoor::CloseDoor()
{
	// this needs to be refactored

	return; // part way through lecture on blue print events
}

const float UOpenDoor::GetNetMassOnTriggerPlate()
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