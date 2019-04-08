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
	// Unreal handles rotations with Quaternions, need to figure out how to euler rotation in specfic axis

	FRotator rotator(0.0f, m_defaultDoorYaw, 0.0f); // Docs say it's in degrees, use Yaw.

	m_owner->SetActorRotation(rotator);

	FString startingRotatorStr = rotator.ToString();

	// ...
	UE_LOG(LogTemp, Warning, TEXT("UOpenDoor::BeginPlay() called on %s starting rotator %s"), *ownerName, *startingRotatorStr);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

