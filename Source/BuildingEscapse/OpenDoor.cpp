// (learning unreal)

#include "OpenDoor.h"
#include "Gameframework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
	: m_owner(nullptr)
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

	const float netMassOnTriggerPlate = GetNetMassOnTriggerPlate();

	if (netMassOnTriggerPlate >= RequiredMassToOpen)
	{
		OnOpen.Broadcast();
	}
	else if (netMassOnTriggerPlate < RequiredMassToOpen)
	{
		OnClose.Broadcast();
	}
}

const float UOpenDoor::GetNetMassOnTriggerPlate()
{
	// query the plate trigger volume for all actors, sum mass and return
	float netMass = 0.0f;

	if (DoorOpenTriggerVolume == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s's OpenDoor::GetNetMassOnTriggerPlate() can't run due to lack of a trigger volume"), *GetOwner()->GetName());
		return netMass;
	}
	
	TArray<AActor*> l_overlappingActors;
	DoorOpenTriggerVolume->GetOverlappingActors(l_overlappingActors); // could 

	for (const auto& actorRef : l_overlappingActors)
	{
		// UE_LOG(LogTemp, Warning, TEXT("UOpenDoor::GetNetMassOnTriggerPlate() picked up %s"), *actorRef->GetName());
		netMass += actorRef->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	UE_LOG(LogTemp, Log, TEXT("UOpenDoor::GetNetMassOnTriggerPlate() returned %f"), netMass);
	return netMass;
}