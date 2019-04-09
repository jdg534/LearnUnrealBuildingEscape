// (learning unreal)

#include "OpenDoor.h"
#include "Gameframework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
	: m_owner(nullptr)
	, m_doorYaw(-10.0f)
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

	OpenDoorFor = world->GetFirstPlayerController()->GetPawn();


	if(DoorOpenTriggerVolume && OpenDoorFor)
	{
		const FString openForName = OpenDoorFor->GetName();
		const FString triggerVolumeName = DoorOpenTriggerVolume->GetName();
		UE_LOG(LogTemp, Warning, TEXT("UOpenDoor %s has trigger volume %s associated and will open for %s"), *ownerName, *triggerVolumeName, *openForName);
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
	// polling for now, need to add a on collide callback
	if (DoorOpenTriggerVolume->IsOverlappingActor(OpenDoorFor))
	{
		OpenDoor();
	}
	else
	{
		CloseDoor();
	}
}


void UOpenDoor::OpenDoor()
{
	FRotator rotator(0.0f, c_DoorOpenYaw, 0.0f); // Docs say it's in degrees, use Yaw.
	m_owner->SetActorRotation(rotator);
}

void UOpenDoor::CloseDoor()
{
	FRotator rotator(0.0f, 0.0f, 0.0f);
	m_owner->SetActorRotation(rotator);
}