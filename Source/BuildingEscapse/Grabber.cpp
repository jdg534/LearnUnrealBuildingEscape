// (learning unreal)

#include "Grabber.h"
#include "Gameframework/Actor.h"

#include <Runtime/Engine/Classes/Engine/World.h>

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
		UE_LOG(LogTemp, Warning, TEXT("UGrabber couldn't get a pointer to the default player controller"));
	}

	m_PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!m_PhysicsHandleComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("UGrabber on %s couldn't get a pointer to a PhysicsHandleComponent"), *GetOwner()->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// remember that float values are in cm

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	m_playerControllerPtr->GetPlayerViewPoint(m_position, m_rotation);

	UWorld* worldPtr = GetWorld();

	UE_LOG(LogTemp, Warning, TEXT("UGrabber::BeginPlay() called"));
	const FString posStr = m_position.ToString();
	const FString rotationStr = m_rotation.ToString();
	const FVector rotationAsUnitVector = m_rotation.Vector();
	UE_LOG(LogTemp, Warning, TEXT("UGrabber is positioned at %s and has rotation %s facing direction %s"), *posStr, *rotationStr, *rotationAsUnitVector.ToString());
	constexpr FColor debugLineColour(255, 0, 0);
	const FVector lineEndPos = m_position + (rotationAsUnitVector * Reach);
	DrawDebugLine(worldPtr, m_position, lineEndPos, debugLineColour, false, 0.0f, 0, 10.0f);

	
	// ray cast checks
	FHitResult hitResult;
	FCollisionQueryParams queryParams(FName(TEXT("")), false, GetOwner());

	bool hit =
	worldPtr->LineTraceSingleByObjectType(
		hitResult,
		m_position,
		lineEndPos,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		queryParams
	);

	if (hit)
	{
		const AActor* hitActor = hitResult.GetActor();
		if (hitActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("The ray cast has hit %s"), *hitActor->GetName());
		}
	}
}

