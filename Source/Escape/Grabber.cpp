// tutorial said to fill out copyright section so i guess copyright david tenni 2021 although can you copyright code from a tutorial probs not idek whatever its done now

#include "DrawDebugHelpers.h"
#include "Grabber.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	// ...
	FindPhysicsHandle();
	InitialiseInputComponent();

}

void UGrabber::FindPhysicsHandle() 
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {}//checking component exists
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No PhysicsHandleComponent is attached to: %s"), *GetOwner()->GetName());
	}
}

void UGrabber::InitialiseInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>(); //since its  default on pawn doent need a null check
	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Error, TEXT("Grab"));

}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Error, TEXT("Release"));

}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//get player viewpoint
	GetReachableObject();

}

FHitResult UGrabber::GetReachableObject() const
{
	FVector PlayerViewLocation = Player->GetActorLocation();
	FRotator PlayerViewRotation = Player->GetActorRotation();
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewLocation, OUT PlayerViewRotation);
	//UE_LOG(LogTemp, Log, TEXT("player location is %s player rotation is %s"), *PlayerViewLocation.ToString(), *PlayerViewRotation.ToString() );
	//linetraceToDistance based on reach
	FVector LineTraceDirection = PlayerViewRotation.Vector();
	FVector LineTraceEnd = PlayerViewLocation + PlayerViewRotation.Vector() * ReachDistance;
	//Visualise Reach Range
	//DrawDebugLine(GetWorld(), PlayerViewLocation, LineTraceEnd, FColor(0, 0, 255), false, 1.0f, 1, 5);

	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams
	);

	AActor* ActorHit = Hit.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Log, TEXT("Actor within reach is: %s"), *(ActorHit->GetName()));
	}
	return Hit;
}

