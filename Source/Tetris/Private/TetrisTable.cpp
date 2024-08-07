// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisTable.h"

UTetrisTable::UTetrisTable()
{
	Columns = 8;
	Rows = 15;
	DistanceBetweenCells = 100.f;
	TableInitialPoint = FVector::ZeroVector;
	InitilizeTable();
}

FVector UTetrisTable::GetCellWorldPosition(const int32& inZ, const int32& inY)
{
	FVector Location = TableInitialPoint;
	Location.Z += inZ * DistanceBetweenCells;
	Location.Y += inY * DistanceBetweenCells;
	return Location;
}

void UTetrisTable::CreateTetrisTable()
{
	for (int32 i = 0; i < Rows; ++i)
	{
		for (int32 j = 0; j < Columns; j++)
		{
			TetrisTable[i][j] = true;
		}
	}
}

void UTetrisTable::GetCellCordinates(const FVector& Location, int32& OutZ, int32 OutY)
{
	FVector AdjustedVector = Location - TableInitialPoint;

	OutZ = FMath::FloorToInt32(AdjustedVector.Z / DistanceBetweenCells);
	OutY = FMath::FloorToInt32(AdjustedVector.Y / DistanceBetweenCells);

	OutZ = FMath::Clamp<int32>(OutZ, 0, Rows - 1);
	OutY = FMath::Clamp<int32>(OutY, 0, Columns - 1);
}

void UTetrisTable::SetTableElement(const int32& inZ, const int32& inY, bool Value)
{
	if (inZ >= 0 && inZ < 15 && inY >= 0 && inY < 15)
	{
		TetrisTable[inZ][inY] = Value;
	}
}

bool UTetrisTable::GetTableElement(const int32& inZ, const int32& inY)
{
	if (inZ >= 0 && inZ < 15 && inY >= 0 && inY < 15)
	{
		return TetrisTable[inZ][inY];
	}
	return false;
}

void UTetrisTable::SetObjectElementAtIndex(const int32& inZ, const int32& inY, AObjectUnit* Value)
{
	if (inZ >= 0 && inZ < 15 && inY >= 0 && inY < 15)
	{
		Objects[inZ][inY] = Value;
	}
}

AObjectUnit* UTetrisTable::GetObjectElementAtIndex(const int32& inZ, const int32& inY)
{
	if (inZ >= 0 && inZ < 15 && inY >= 0 && inY < 15)
	{
		return Objects[inZ][inY];
	}
	return nullptr;
}

void UTetrisTable::PlaceObjectOnTable(AActor* ActorToSpawn, const int32& inZ, const int32& inY)
{
}

void UTetrisTable::DePlaceObjectOnTable(AActor* ActorToRemove)
{
}

void UTetrisTable::InitilizeTable()
{
	TetrisTable.SetNum(Rows);
	Objects.SetNum(Rows);

	for (int32 i = 0; i < Rows; i++)
	{
		TetrisTable[i].SetNum(Columns);
		Objects[i].SetNum(Columns);
	}

	CreateTetrisTable();
}
