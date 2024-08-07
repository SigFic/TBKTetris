// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TetrisController.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFinishGameDelegate);

UCLASS()
class TETRIS_API ATetrisController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ATetrisController();

	/*
	* @param amount determines how many object will return
	*/
	UFUNCTION(BlueprintCallable)
	TArray<class AObjectUnit* > GetObjects(int32 amount);

	/*
	* @param amaount determines how many ObjectUnit will added UnRelatedObjects array
	*/
	UFUNCTION(BlueprintCallable)
	void ExtendUnRelatedObjects(int32 amount);

	UFUNCTION(BlueprintCallable)
	void MoveDownContinously();

	UFUNCTION(BlueprintCallable)
	bool CheckifLaneCompleted(int32 ZIndex);

	UFUNCTION(BlueprintCallable)
	void StartMoveDownTimer();

	void AddUnitObjectToUnrelatedObjects(TArray<class AObjectUnit*> Array);

protected:

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Unit", meta = (AllowPrivateAccess = "true"))
	TArray<class AObjectUnit*> UnRelatedObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Unit", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AObjectUnit> UnitClass;

	UPROPERTY()
	class UTetrisTable* TTRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objects", meta = (AllowPrivateAccess = "true"))
	class AMainObject* ActiveMainObjectRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objects", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AMainObject>> MainObjectClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objects", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed;

	float ActiveMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point", meta = (AllowPrivateAccess = "true"))
	int32 Point;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point", meta = (AllowPrivateAccess = "true"))
	int32 MaxPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point", meta = (AllowPrivateAccess = "true"))
	int32 PointIncrementAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* BackGroundSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* DownFastSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* MoveSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* LaneCrashed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* ObjectPopUpSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (AllowPrivateAccess = "true"))
	bool bIsGameEnded;
	
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FFinishGameDelegate FinishGameEvent;

	FTimerHandle SecondTimerHandle;

	UPROPERTY()
	TArray<int32> ZIndexesArray;

private:

	void BubleSort(TArray<int32>& Array);

	int32 MainObjectCounter = 1;

	void IncrementMainObjectCounter();



};
