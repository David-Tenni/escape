// tutorial said to fill out copyright section so i guess copyright david tenni 2021 although can you copyright code from a tutorial probs not idek whatever its done now

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	void FindAudioComponent();
	float TotalMassInVolume() const;

private:
	float InitialYaw;
	float CurrentYaw;

	UPROPERTY(EditAnywhere)
	float RequiredMassToOpen = 50.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* DoorOpenTrigger;
	
	UAudioComponent* DoorAudio = nullptr;

	UPROPERTY(EditAnywhere)
	float OpenTargetYaw = 90.f;

	UPROPERTY(EditAnywhere)
	float OpenDoorSpeed = 2.f;

	UPROPERTY(EditAnywhere)
	float CloseDoorSpeed = 1.f;

	UPROPERTY(EditAnywhere)
		AActor* ActorThatOpens = nullptr;

	float DoorLastOpened = 0.f;
	
	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 0.1781105f;
};
