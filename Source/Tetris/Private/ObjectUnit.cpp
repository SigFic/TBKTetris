// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectUnit.h"
#include "TetrisGameMode.h"
#include "TetrisTable.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObjectUnit::AObjectUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UnitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	UnitMesh->SetupAttachment(RootComponent);

	bIsMovingRightNow = false;

}

// Called when the game starts or when spawned
void AObjectUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjectUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjectUnit::SetObjectLocation(const FVector InitialPoint, const int32& inZ, const int32& inY)
{
	FVector Location = InitialPoint;
	Location.Z += (inZ * 100.f) + 50.f;
	Location.Y += (inY * 100.f) + 50.f;

	SetActorLocation(Location);
}

bool AObjectUnit::CheckifObjectCanMoveDown()
{
	if (ObjectZ == 0) return false;
	
	ATetrisGameMode* GMRef = Cast<ATetrisGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GMRef && GMRef->TetrisTableInstance)
	{
		if (GMRef->TetrisTableInstance->GetTableElement(ObjectZ - 1, ObjectY))
		{
			return true;
		}
		else
		{
			AObjectUnit* UnitRef =  GMRef->TetrisTableInstance->GetObjectElementAtIndex(ObjectZ - 1, ObjectY);

			if (UnitRef)
			{
				return (UnitRef->bIsMovingRightNow);
			}
			return false;
		}
	}
	return false;
}

bool AObjectUnit::CheckifObjectCanMoveSide(bool Side)
{
	if (Side)
	{
		ATetrisGameMode* GMRef = Cast<ATetrisGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GMRef && GMRef->TetrisTableInstance)
		{
			if (ObjectY == (GMRef->TetrisTableInstance->Columns - 1)) return false;

			if (GMRef->TetrisTableInstance->GetTableElement(ObjectZ, ObjectY + 1))
			{
				return true;
			}
			else
			{
				AObjectUnit* UnitRef = GMRef->TetrisTableInstance->GetObjectElementAtIndex(ObjectZ, ObjectY + 1);
				if (UnitRef)
				{
					return (UnitRef->bIsMovingRightNow);
				}
				return false;
			}
		}
		return false;
	}
	else
	{
		ATetrisGameMode* GMRef = Cast<ATetrisGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GMRef && GMRef->TetrisTableInstance)
		{
			if (ObjectY == 0) return false;

			if (GMRef->TetrisTableInstance->GetTableElement(ObjectZ, ObjectY - 1))
			{
				return true;
			}
			else
			{
				AObjectUnit* UnitRef = GMRef->TetrisTableInstance->GetObjectElementAtIndex(ObjectZ, ObjectY - 1);
				if (UnitRef)
				{
					return (UnitRef->bIsMovingRightNow);
				}
				return false;
			}
		}
		return false;
	}
}

bool AObjectUnit::CheckifObjectCanTurn(const int32& MainZ, const int32& MainY, int32& OutNewZ, int32& OutNewY)
{
	ATetrisGameMode* GMRef = Cast<ATetrisGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GMRef || !GMRef->TetrisTableInstance)
	{
		return false;
	}


	int32 ZDiff = ObjectZ - MainZ;
	int32 YDiff = ObjectY - MainY;

	int32 NewZDiff = - YDiff;
	int32 NewYDiff = ZDiff;

	OutNewZ = MainZ + NewZDiff;
	OutNewY = MainY + NewYDiff;

	if (OutNewZ >= 0 && OutNewZ < GMRef->TetrisTableInstance->Rows && OutNewY >= 0 && OutNewY < GMRef->TetrisTableInstance->Columns)
	{
		if (GMRef->TetrisTableInstance->GetTableElement(OutNewZ, OutNewY))
		{
			return true;
		}
		else
		{
			AObjectUnit* UnitRef = GMRef->TetrisTableInstance->GetObjectElementAtIndex(OutNewZ, OutNewY);

			if (UnitRef)
			{
				return (UnitRef->bIsMovingRightNow);
			}
			return false;
		}
	}
	else return false;
}

void AObjectUnit::SetObjectZandY(const int32& inZ, const int32& inY)
{
	if (inZ >= 0 && inZ < 15)
	{
		this->ObjectZ = inZ;
	}
	
	if (inY >= 0 && inY < 15)
	{
		this->ObjectY = inY;
	}
}

void AObjectUnit::GetObjectZandY(int32& OutZ, int32& OutY)
{
	OutZ = ObjectZ;
	OutY = ObjectY;
}




