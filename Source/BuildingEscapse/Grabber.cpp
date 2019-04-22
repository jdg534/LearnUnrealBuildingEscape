// (learning unreal)

#include "Grabber.h"
#include "Gameframework/Actor.h"

#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
	: m_playerControllerPtr(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("UGrabber::BeginPlay() called"));

	m_playerControllerPtr = GetWorld()->GetFirstPlayerController();
	if (!m_playerControllerPtr)
	{ 
		UE_LOG(LogTemp, Error, TEXT("UGrabber couldn't get a pointer to the default player controller"));
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// remember that float values are in cm

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	m_playerControllerPtr->GetPlayerViewPoint(m_position, m_rotation);

	UE_LOG(LogTemp, Warning, TEXT("UGrabber::BeginPlay() called"));
	const FString posStr = m_position.ToString();
	const FString rotationStr = m_rotation.ToString();
	const FVector rotationAsUnitVector = m_rotation.Vector();
	UE_LOG(LogTemp, Warning, TEXT("UGrabber is positioned at %s and has rotation %s facing direction %s"), *posStr, *rotationStr, *rotationAsUnitVector.ToString());
	constexpr FColor debugLineColour(255, 0, 0);
	const FVector debugLineEndPos = m_position + (rotationAsUnitVector * Reach);
	DrawDebugLine(GetWorld(), m_position, debugLineEndPos, debugLineColour, false, 0.0f, 0, 10.0f);
}

