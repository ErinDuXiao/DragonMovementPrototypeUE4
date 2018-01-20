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

	class AActor* Head;

	TArray<class AActor*> Segments;

	float CurrentSpeed;

	// TODO: Make state machine
	FVector TargetLocation;

protected:
	virtual void BeginPlay() override;

public:	
	ADragonBase();
		
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Category = Setup, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Length"))
		int InitialLength;

	UPROPERTY(Category = Setup, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Speed", ClampMin = 0.1f, ClampMax = 150.0f))
		float Speed;

	UPROPERTY(Category = Setup, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "RotationSpeed", ClampMin = 0.1f, ClampMax = 150.0f))
		float RotationSpeed;

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

};