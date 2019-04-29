// (learning unreal)

#include "Grabber.h"
#include "Gameframework/Actor.h"

#include <Runtime/Engine/Classes/Engine/World.h>

#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
	: m_playerControllerPtr(nullptr)
	, m_actorInputComponent(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	bool initialisedComponents = FindPhysicsHandleComponent() && FindPlayerController() && FindInputComponent();

	if (!initialisedComponents)
	{
		UE_LOG(LogTemp, Error, TEXT("UGrabber failed initialisation, see above error messages"));
		return;
	}
	BindActions();	
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// remember that float values are in cm

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// update "grabbed" actor if holding
	if (m_PhysicsHandleComponent->GrabbedComponent)
	{
		FVector position;
		FRotator rotation;

		m_playerControllerPtr->GetPlayerViewPoint(position, rotation);

		const FVector rotationAsUnitVector = rotation.Vector();
		const FVector lineEndPos = position + (rotationAsUnitVector * Reach);
		m_PhysicsHandleComponent->SetTargetLocation(lineEndPos);
	}
}

bool UGrabber::FindPhysicsHandleComponent()
{
	m_PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!m_PhysicsHandleComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("UGrabber on %s couldn't get a pointer to a PhysicsHandleComponent"), *GetOwner()->GetName());
		return false;
	}
	return true;
}

bool UGrabber::FindPlayerController()
{
	m_playerControllerPtr = GetWorld()->GetFirstPlayerController();
	if (!m_playerControllerPtr)
	{
		UE_LOG(LogTemp, Error, TEXT("UGrabber couldn't get a pointer to the default player controller"));
		return false;
	}
	return true;
}

bool UGrabber::FindInputComponent()
{
	m_actorInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!m_actorInputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("UGrabber on %s couldn't get a pointer to a Input Component"), *GetOwner()->GetName());
		return false;
	}
	return true;
}

void UGrabber::BindActions()
{
	m_actorInputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	m_actorInputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
}

const FHitResult UGrabber::GetFirstPhysicBodyInReach() const
{
	FVector position;
	FRotator rotation;

	m_playerControllerPtr->GetPlayerViewPoint(position, rotation);

	UWorld* worldPtr = GetWorld();

	const FVector rotationAsUnitVector = rotation.Vector();
	const FVector lineEndPos = position + (rotationAsUnitVector * Reach);

	// uncomment if we need the grab range
	// constexpr FColor debugLineColour(255, 0, 0);
	// DrawDebugLine(worldPtr, m_position, lineEndPos, debugLineColour, false, 0.0f, 0, 10.0f);

	// ray cast checks
	FHitResult hitResult;
	FCollisionQueryParams queryParams(FName(TEXT("")), false, GetOwner());

	bool hit =
		worldPtr->LineTraceSingleByObjectType(
			hitResult,
			position,
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
	return hitResult;
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("UGrabber::Grab() called"));

	// ray cast for a actor with the physics body collision channel
	
	FHitResult hitRes = GetFirstPhysicBodyInReach();
	UPrimitiveComponent* ComponentToGrab = hitRes.GetComponent();
	AActor* hitActor = hitRes.GetActor();
	
	if (hitActor)
	{
		// attach physics handle (TODO)
		m_PhysicsHandleComponent->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true); // true = allow rotation
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("UGrabber::Release() called"));

	// release the physics handle if attached
	m_PhysicsHandleComponent->ReleaseComponent();
}