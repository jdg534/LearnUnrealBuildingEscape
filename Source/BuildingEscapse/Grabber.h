// (learning unreal)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
	APlayerController* m_playerControllerPtr;
	FVector m_position;
	FRotator m_rotation;

	// how long the grabber's reach is, this is in cm
	UPROPERTY(EditAnywhere)
	float Reach = 100.0f; // default value

	// UPROPERTY(EditAnywhere)
	UPhysicsHandleComponent* m_PhysicsHandleComponent = nullptr;
};
