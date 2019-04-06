// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"
#include "Gameframework/Actor.h"

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__));
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();
	m_ownerName = GetOwner()->GetName();
	m_owerTransform = GetOwner()->GetTransform();
	const FVector ownerPos = m_owerTransform.GetLocation();
	m_positionString = ownerPos.ToString();
	UE_LOG(LogTemp, Warning, TEXT("UPositionReport::BeginPlay() called on %s positioned at %s"), *m_ownerName, *m_positionString);
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

