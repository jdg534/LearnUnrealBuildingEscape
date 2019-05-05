// (learning unreal)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPSE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool FindPhysicsHandleComponent();
	bool FindPlayerController();
	bool FindInputComponent();
	void BindActions();

	const FHitResult GetFirstPhysicBodyInReach() const; // can't be const, m_playerControllerPtr->GetPlayerViewPoint 

	void Grab();
	void Release();

	APlayerController* m_playerControllerPtr = nullptr;

	// how long the grabber's reach is, this is in cm
	UPROPERTY(EditAnywhere)
	float Reach = 100.0f; // default value

	// UPROPERTY(EditAnywhere)
	UPhysicsHandleComponent* m_PhysicsHandleComponent = nullptr;

	UInputComponent* m_actorInputComponent = nullptr;

	FVector m_position;
	FRotator m_rotator; // not to be confused with rotation, need to
};
