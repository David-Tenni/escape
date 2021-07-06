// tutorial said to fill out copyright section so i guess copyright david tenni 2021 although can you copyright code from a tutorial probs not idek whatever its done now


#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
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
	FindAudioComponent();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!DoorOpenTrigger)
	{
		UE_LOG(LogTemp, Error, TEXT("OpenDoorTrigger not set on %s"), *GetOwner()->GetFName().ToString());
	}	

}

void UOpenDoor::FindAudioComponent()
{
	DoorAudio = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!DoorAudio) //checking component exists
	{
		UE_LOG(LogTemp, Error, TEXT("No AudioComponent is attached to: %s"), *GetOwner()->GetName());
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassInVolume() > RequiredMassToOpen)
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
	
	DoorAudio->Play();
	
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
float UOpenDoor::TotalMassInVolume() const
{
	float TotalMass = 0.f;
	if (!DoorOpenTrigger) { return TotalMass; }

	TArray<AActor*> OverlappingActors;
	
	DoorOpenTrigger->GetOverlappingActors(OverlappingActors);

	for(AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}