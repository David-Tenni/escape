// tutorial said to fill out copyright section so i guess copyright david tenni 2021 although can you copyright code from a tutorial probs not idek whatever its done now


#include "OpenDoor.h"
#include"GameFramework/actor.h"
#include "EngineMinimal.h"
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
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenTargetYaw += InitialYaw;
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!DoorOpenTrigger)
	{
		UE_LOG(LogTemp, Error, TEXT("OpenDoorTrigger not set on %s"), *GetOwner()->GetFName().ToString());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (DoorOpenTrigger && DoorOpenTrigger->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else 
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
	

	
}

void UOpenDoor::OpenDoor(float DeltaTime) 
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, OpenTargetYaw, DeltaTime, OpenDoorSpeed);

	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime) 
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, CloseDoorSpeed);

	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}