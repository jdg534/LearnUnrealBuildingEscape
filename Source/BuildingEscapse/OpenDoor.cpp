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
		UE_LOG(LogTemp, Warning, TEXT("UOpenDoor %s needs a trigger volume and Actor to open for"), *ownerName);
	}

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// will need an overlap event 

	if (GetNetMassOnTriggerPlate() >= RequiredMassToOpen)
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
	FRotator rotator(0.0f, c_DoorOpenYaw, 0.0f); // Docs say it's in degrees, use Yaw.
	m_owner->SetActorRotation(rotator);
	m_doorOpen = true;
	m_timeOfLastOpenDoor = GetWorld()->GetTimeSeconds();
}

void UOpenDoor::CloseDoor()
{
	FRotator rotator(0.0f, DoorClosedYaw, 0.0f);
	m_owner->SetActorRotation(rotator);
	m_doorOpen = false;
}

const float UOpenDoor::GetNetMassOnTriggerPlate()
{
	// query the plate trigger volume for all actors, sum mass and return
	float netMass = 0.0f;
	TArray<AActor*> l_overlappingActors;
	DoorOpenTriggerVolume->GetOverlappingActors(l_overlappingActors); // could 

	const int32 iActorCount = l_overlappingActors.Num();
	for (const auto& actorRef : l_overlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("UOpenDoor::GetNetMassOnTriggerPlate() picked up %s"), *actorRef->GetName());
		netMass += actorRef->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return netMass;
}