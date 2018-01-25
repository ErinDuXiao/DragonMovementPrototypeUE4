// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HeadSegmentBase.h"
#include "DragonBase.generated.h"

UCLASS()
class DRAGONPROTO_API ADragonBase : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:	
	ADragonBase();
		
	UPROPERTY(Category = IngameVariable, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Head"))
	class AActor* Head;

	UPROPERTY(Category = IngameVariable, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Segments"))
	TArray<class AActor*> Segments;
	
	UPROPERTY(Category = IngameVariable, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "CurrentSpeed"))
	float CurrentSpeed;

	// TODO: Make state machine
	UPROPERTY(Category = IngameVariable, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "TargetLocation"))
	FVector TargetLocation;


	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Category = Setup, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "DebugNoMove", ClampMin = 0.0f, ClampMax = 100.0f))
		bool DebugNoMove;

	UPROPERTY(Category = Setup, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Length"))
		int InitialLength;

	UPROPERTY(Category = Setup, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Speed", ClampMin = 0.1f, ClampMax = 150.0f))
		float Speed;

	UPROPERTY(Category = Setup, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "RotationSpeed", ClampMin = 0.1f, ClampMax = 150.0f))
		float TurnSpeed;

	UPROPERTY(Category = Setup, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "BalancingSpeed", ClampMin = 0.1f, ClampMax = 150.0f))
		float BalancingSpeed;

	UPROPERTY(Category = Setup, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "WaveSpeed", ClampMin = 0.1f, ClampMax = 100000.0f))
		float WaveSpeed;

	UPROPERTY(Category = Setup, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "WaveScale", ClampMin = 0.000001f, ClampMax = 1.0f))
		float WaveScale;

	UPROPERTY(Category = Setup, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "SpeedScale", ClampMin = 0.1f, ClampMax = 150.0f))
		float SpeedScale;

	UPROPERTY(Category = Setup, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "MinDistanceOfSegments", ClampMin = 0.0f, ClampMax = 100.0f))
		float MinDistanceOfSegments;

	UPROPERTY(Category = Setup, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "HeadPartClass"))
		class TSubclassOf<class AActor> HeadPartClass;

	UPROPERTY(Category = Setup, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "BodyPartClass"))
		class TSubclassOf<class AActor> BodyPartClass;
	
	UFUNCTION(BlueprintCallable)
		virtual void Move(float DeltaTime);
	
	UFUNCTION(BlueprintCallable)
		virtual void FindTarget();

	UFUNCTION(BlueprintCallable)
		int GetTurnDirection(FVector forward, FVector location, FVector targetLocationVector);
};