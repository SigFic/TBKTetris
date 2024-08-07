// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TetrisTable.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TETRIS_API UTetrisTable : public UObject
{
	GENERATED_BODY()

public:
	UTetrisTable();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TetrisTable")
	FVector TableInitialPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TetrisTable")
	int32 Columns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TetrisTable")
	int32 Rows;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TetrisTable")
	int32 DistanceBetweenCells;



public:

	UFUNCTION(BlueprintCallable)
	FVector GetCellWorldPosition(const int32& inZ, const int32& inY);
	
	UFUNCTION(BlueprintCallable)
	void CreateTetrisTable();

	UFUNCTION(BlueprintCallable)
	void GetCellCordinates(const FVector& Location, int32& OutZ, int32 OutY);

	UFUNCTION(BlueprintCallable)
	void SetTableElement(const int32& inZ, const int32& inY, bool Value);

	UFUNCTION(BlueprintCallable)
	bool GetTableElement(const int32& inZ, const int32& inY);

	UFUNCTION(BlueprintCallable)
	void SetObjectElementAtIndex(const int32& inZ, const int32& inY, AObjectUnit* Value);

	UFUNCTION(BlueprintCallable)
	AObjectUnit* GetObjectElementAtIndex(const int32& inZ, const int32& inY);

	UFUNCTION(BlueprintCallable)
	void PlaceObjectOnTable(AActor* ActorToSpawn, const int32& inZ, const int32& inY);

	UFUNCTION(BlueprintCallable)
	void DePlaceObjectOnTable(AActor* ActorToRemove);

private:

	TArray<TArray< bool >> TetrisTable;

	TArray<TArray<class AObjectUnit*>> Objects;

private:

	void InitilizeTable();

};
