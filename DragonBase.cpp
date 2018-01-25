// Fill out your copyright notice in the Description page of Project Settings.

#include "DragonBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADragonBase::ADragonBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set default values to setup this class.
	CurrentSpeed = 1.0f;
	InitialLength = 10;
	Speed = 1.0f;
	TurnSpeed = 1.0f;
	BalancingSpeed = 1.0f;
	WaveSpeed = 300.0f;
	WaveScale = 0.01f;
	SpeedScale = 150.0f;
	MinDistanceOfSegments = 100.0f;

}

// Called when the game starts or when spawned
void ADragonBase::BeginPlay()
{
	Super::BeginPlay();

	UWorld * const World = GetWorld();

	// Guard from wrong setup
	if (HeadPartClass == nullptr || BodyPartClass == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("DragonBase is not setup properly."));
		return;
	}

	// Instansiate head parts
	Head = World->SpawnActor<AActor>(HeadPartClass);

	// Move to spawn point
	Head->SetActorLocation(GetActorLocation());

	// Attach the head to myself
	Head->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));

	// Initialize segments array
	Segments = TArray<class AActor*>();

	// Add head to the body parts array
	Segments.Add(Head);

	FVector prev = Head->GetActorLocation();

	// Append body parts
	for (int i = 1; i < InitialLength; i++) {
		AActor* segment = World->SpawnActor<AActor>(BodyPartClass);
		prev.Y = prev.Y + MinDistanceOfSegments;

		segment->SetActorLocation(prev);
		segment->SetActorScale3D(segment->GetActorScale() / (i / 3));

		// Attach the segment to myself
		segment->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));

		// Add body parts to segments array
		Segments.Add(segment);

		prev = segment->GetActorLocation();
	}

	
}

// Called every frame
void ADragonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DebugNoMove) {
		return;
	}

	// Guard from wrong setup
	if (HeadPartClass == nullptr || BodyPartClass == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("DragonBase is not setup properly."));
		return;
	}

	FindTarget();
	
	Move(DeltaTime);

}

// TODO: Move this to AI Controller
void ADragonBase::Move(float DeltaTime) {

	// Check if I know my target

	// Move head
	if (TargetLocation.IsZero()) 
		return;

	TargetLocation.Z = FMath::Sin(GFrameNumber * WaveScale) * WaveSpeed + TargetLocation.Z;
	UE_LOG(LogTemp, Warning, TEXT("%d"), (int)GFrameNumber);

	Head->SetActorLocation(FMath::Lerp(Head->GetActorLocation(), TargetLocation, Speed / SpeedScale));
	Head->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(Head->GetActorLocation(), TargetLocation));

	AActor* prevSegment = Head;

	// Move body parts
	for (int i = 1; i < Segments.Num(); i++) {

		AActor* currentSegment = Segments[i];
		FVector currentLocation = currentSegment->GetActorLocation();
		FVector prevLocation = prevSegment->GetActorLocation();

		float distance = FVector::Dist(currentLocation, prevLocation);
		float alpha = DeltaTime * distance / MinDistanceOfSegments * CurrentSpeed;

		currentSegment->SetActorLocation(FMath::Lerp(currentLocation, prevLocation, alpha));
		currentSegment->SetActorRotation(FMath::Lerp(currentSegment->GetActorRotation(), prevSegment->GetActorRotation(), alpha));

		prevSegment = currentSegment;

	}


}

void ADragonBase::FindTarget() {

	// TODO: Find random in the world

	// Find player location
	APawn* player = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
	if (player) {
		TargetLocation = player->GetActorLocation();
	}

}


int ADragonBase::GetTurnDirection(FVector forward, FVector location, FVector targetLocationVector) {

	FVector normalizedDelta = (location - targetLocationVector).GetSafeNormal();
	float dotProduct = FVector::DotProduct(normalizedDelta, forward);
	FVector crossProduct = FVector::CrossProduct(normalizedDelta, forward);

	if (crossProduct.Z > 0) {
		// left
		return 1;
	}
	else if (crossProduct.Z < 0) {
		// right
		return -1;
	}

	// straight
	return 0;

}