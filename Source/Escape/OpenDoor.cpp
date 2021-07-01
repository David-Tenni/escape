// tutorial said to fill out copyright section so i guess copyright david tenni 2021 although can you copyright code from a tutorial probs not idek whatever its done now


#include "OpenDoor.h"
#include"GameFramework/actor.h"
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
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
	FRotator ReverseDoorAngle = { 0, -90, 0 };
	float OpenDoorAngle = 90.f;
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Add(0, OpenDoorAngle, 0);
	GetOwner()->SetActorRotation(CurrentRotation);	 
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

