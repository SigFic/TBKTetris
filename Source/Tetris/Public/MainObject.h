// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainObject.generated.h"

UCLASS()
class TETRIS_API AMainObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool MoveLeft();

	UFUNCTION(BlueprintCallable)
	bool MoveRight();

	UFUNCTION(BlueprintCallable)
	bool MoveDown();

	UFUNCTION(BlueprintCallable)
	bool Rotate();

	FORCEINLINE TArray<class AObjectUnit*> GetObjects() { return Objects; }

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InitialObject();
		
	void DecrementObjectCounter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Unit", meta = (AllowPrivateAccess = "true"))
	//TArray<FTransform> ObjectTransforms;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Unit", meta = (AllowPrivateAccess = "true"))
	int32 ObjectCounter = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Unit", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AObjectUnit> ObjectUnitClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Unit", meta = (AllowPrivateAccess = "true"))
	TArray<AObjectUnit*> Objects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials", meta = (AllowPrivateAccess = "true"))
	TArray<class UMaterialInstance*> Materials;

	TMap<AObjectUnit*, FVector2D> ObjectToNewLocation;
};
