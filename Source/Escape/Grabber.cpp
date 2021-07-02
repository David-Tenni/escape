// tutorial said to fill out copyright section so i guess copyright david tenni 2021 although can you copyright code from a tutorial probs not idek whatever its done now

#include "DrawDebugHelpers.h"
#include "Grabber.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
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
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//get player viewpoint

	FVector PlayerViewLocation = Player->GetActorLocation();
	FRotator PlayerViewRotation = Player->GetActorRotation();
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewLocation, OUT PlayerViewRotation);
	//UE_LOG(LogTemp, Log, TEXT("player location is %s player rotation is %s"), *PlayerViewLocation.ToString(), *PlayerViewRotation.ToString() );
	//linetraceToDistance based on reach
	FVector LineTraceDirection = PlayerViewRotation.Vector();
	FVector LineTraceEnd = PlayerViewLocation + FVector(0.f, 100.f, 0.f);
	DrawDebugLine(GetWorld(), PlayerViewLocation, LineTraceEnd, FColor(0, 0, 255), false, 1.0f, 1, 5);
}

