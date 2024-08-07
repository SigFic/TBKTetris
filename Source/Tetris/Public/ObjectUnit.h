// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectUnit.generated.h"

UCLASS()
class TETRIS_API AObjectUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectUnit();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "object")
	bool bIsMovingRightNow;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetObjectLocation(const FVector InitialPoint, const int32& inZ, const int32& inY);

	UFUNCTION(BlueprintCallable)
	bool CheckifObjectCanMoveDown();

	/*
	@param side - 0 means left , 1 means right*/
	UFUNCTION(BlueprintCallable)
	bool CheckifObjectCanMoveSide(bool Side);

	UFUNCTION(BlueprintCallable)
	bool CheckifObjectCanTurn(const int32& MainZ, const int32& MainY, int32& OutNewZ, int32& OutNewY);

	UFUNCTION(BlueprintCallable)
	void SetObjectZandY(const int32& inZ, const int32& inY);

	UFUNCTION(BlueprintCallable)
	void GetObjectZandY(int32& OutZ, int32& OutY);

	class AMainObject* MainOwner;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* UnitMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "object", meta = (AllowPrivateAccess = "true"))
	int32 ObjectZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "object", meta = (AllowPrivateAccess = "true"))
	int32 ObjectY;




};
