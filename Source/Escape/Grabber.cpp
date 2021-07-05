// tutorial said to fill out copyright section so i guess copyright david tenni 2021 although can you copyright code from a tutorial probs not idek whatever its done now

#include "Grabber.h"
#include "DrawDebugHelpers.h"

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
	FindPhysicsHandle();
	InitialiseInputComponent();

}

void UGrabber::FindPhysicsHandle() 
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) //checking component exists
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
	FHitResult HitResult = GetReachableObject();
	HeldObject = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		if (!PhysicsHandle) { return; }
		PhysicsHandle->GrabComponentAtLocation
		(
			HeldObject,
			NAME_None,
			HitResult.Location
		);
	}
}

void UGrabber::Release()
{
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//get player viewpoint
	if (!PhysicsHandle) { return; }
	if(PhysicsHandle->GrabbedComponent)
	{
		
		PhysicsHandle->SetTargetLocation(LineTraceEnd());
	}

}
FVector UGrabber::LineTraceEnd() const
{
	
	FVector PlayerViewLocation = Player->GetActorLocation();
	FRotator PlayerViewRotation = Player->GetActorRotation();
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewLocation, OUT PlayerViewRotation);
	FVector LineTraceDirection = PlayerViewRotation.Vector();
	return PlayerViewLocation + PlayerViewRotation.Vector() * ReachDistance;
}

FHitResult UGrabber::GetReachableObject() const
{
	FVector PlayerViewLocation = Player->GetActorLocation();

	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewLocation,
		LineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams
	);

	AActor* ActorHit = Hit.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Log, TEXT("Actor within reach is: %s"), *(ActorHit->GetName()));
	}
	return Hit;
}

