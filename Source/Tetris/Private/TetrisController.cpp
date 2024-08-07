// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisController.h"
#include "ObjectUnit.h"
#include "MainObject.h"
#include "TetrisTable.h"
#include "Kismet/GameplayStatics.h"
#include "TetrisGameMode.h"

ATetrisController::ATetrisController() :
	bIsGameEnded {false},
	ActiveMoveSpeed{1.f}
{
}

void ATetrisController::BeginPlay()
{
	Super::BeginPlay();
	//UGameplayStatics::PlaySoundAtLocation(this, BackGroundSound, FVector::ZeroVector);
	ATetrisGameMode* GMRef = Cast<ATetrisGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GMRef)
	{
		TTRef = GMRef->TetrisTableInstance;
		ActiveMainObjectRef = GetWorld()->SpawnActor<AMainObject>(MainObjectClasses[FMath::RandRange(0, MainObjectClasses.Num() - 1)], FVector(0.f, 0.f, -2000.f), FRotator::ZeroRotator);
		if (ObjectPopUpSound) UGameplayStatics::PlaySoundAtLocation(this, ObjectPopUpSound, FVector::ZeroVector);
		if (ActiveMainObjectRef)
		{
			ActiveMainObjectRef->InitialObject();

			StartMoveDownTimer();
		}
	}
	ExtendUnRelatedObjects(25);
	
}

TArray<class AObjectUnit*> ATetrisController::GetObjects(int32 amount)
{
	if (amount > UnRelatedObjects.Num())
	{
		ExtendUnRelatedObjects(15);
	}
	TArray<AObjectUnit*> ReturnedArray;
	for (int i = 0; i < amount; i++)
	{
		AObjectUnit* UnitRef =  UnRelatedObjects[UnRelatedObjects.Num()- 1];
		if (UnitRef)
		{
			ReturnedArray.Add(UnitRef);
			UnRelatedObjects.Remove(UnitRef);
		}
	}

	return ReturnedArray;
}

void ATetrisController::ExtendUnRelatedObjects(int32 amount)
{
	UE_LOG(LogTemp, Warning, TEXT("UnRelatedobject has been extended for a %d"), amount);
	for (int i = 0; i < amount; i++)
	{
		AObjectUnit* UnitRef = GetWorld()->SpawnActor<AObjectUnit>(UnitClass, FVector(0.f, 0.f, -2000.f), FRotator::ZeroRotator);
		if (UnitRef)
		{
			UnRelatedObjects.Add(UnitRef);
			UnitRef->MainOwner = nullptr;
		}
	}
}

void ATetrisController::MoveDownContinously()
{
	if (bIsGameEnded) return;
	if (!ActiveMainObjectRef) return;

	if (ActiveMainObjectRef->MoveDown())
	{
		if (MoveSound && MoveSpeed > 0.05)
		{
			UGameplayStatics::PlaySoundAtLocation(this, MoveSound, FVector::ZeroVector);
		}
		return;
	}

	for (AObjectUnit* UnitRef : ActiveMainObjectRef->GetObjects())
	{
		if (!UnitRef) continue;

		int32 UnitZ, UnitY;
		UnitRef->GetObjectZandY(UnitZ, UnitY);
		UnitRef->bIsMovingRightNow = false;

		if (!TTRef) continue;
		TTRef->SetTableElement(UnitZ, UnitY, false);
		TTRef->SetObjectElementAtIndex(UnitZ, UnitY, UnitRef);

		if (TTRef->Rows - 1 <= UnitZ)
		{
			FinishGameEvent.Broadcast();
			bIsGameEnded = true;
		}
		
		ZIndexesArray.AddUnique(UnitZ);
		Point += PointIncrementAmount;
	}

	BubleSort(ZIndexesArray);
	UE_LOG(LogTemp, Warning, TEXT("Z Indexes hase : %d"), ZIndexesArray.Num());

	for (int32 i = 0; i < ZIndexesArray.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Z Indexes : %d"), ZIndexesArray[i]);

		if (CheckifLaneCompleted(ZIndexesArray[i]))
		{
			for (int32 j = i + 1; j < ZIndexesArray.Num(); j++)
			{
				ZIndexesArray[j] = ZIndexesArray[j] - 1;
			}
		}
	}

	ZIndexesArray.Empty();
	ActiveMainObjectRef = GetWorld()->SpawnActor<AMainObject>(MainObjectClasses[FMath::RandRange(0, MainObjectClasses.Num() - 1)] , FVector(0.f, 0.f, -2000.f), FRotator::ZeroRotator);
	if (ObjectPopUpSound) UGameplayStatics::PlaySoundAtLocation(this, ObjectPopUpSound, FVector::ZeroVector);
	if (ActiveMainObjectRef)
	{
		ActiveMainObjectRef->InitialObject();
		IncrementMainObjectCounter();
	}
	MoveSpeed = ActiveMoveSpeed;
	StartMoveDownTimer();
}

bool ATetrisController::CheckifLaneCompleted(int32 ZIndex)
{
	if (bIsGameEnded) return false;
	if (!TTRef) return false;

	for (int32 i = 0; i < TTRef->Columns; i++)
	{
		if (TTRef->GetTableElement(ZIndex, i)) return false;
	}
	AObjectUnit* UnitRef;
	if(LaneCrashed) UGameplayStatics::PlaySoundAtLocation(this, LaneCrashed, FVector::ZeroVector);
	for (int32 i = 0; i < TTRef->Columns; i++)
	{
		TTRef->SetTableElement(ZIndex, i, true);
		UnitRef = TTRef->GetObjectElementAtIndex(ZIndex, i);
		if (!UnitRef) continue;
		UnitRef->SetActorLocation(FVector(0.f, 0.f, -2000.f));
		TTRef->SetObjectElementAtIndex(ZIndex, i, nullptr);
		UnRelatedObjects.Add(UnitRef);
		AMainObject* MORef = UnitRef->MainOwner;
		UnitRef->MainOwner = nullptr;
		if (MORef)
		{
			MORef->DecrementObjectCounter();
		}
		Point += PointIncrementAmount;
	}

	for (int32 i = ZIndex + 1; i < TTRef->Rows; i++)
	{
		for (int32 j = 0; j < TTRef->Columns ; j++)
		{
			if (!TTRef->GetTableElement(i , j))
			{
				TTRef->SetTableElement(i, j, true);
				TTRef->SetTableElement(i - 1, j, false);
				UnitRef = TTRef->GetObjectElementAtIndex(i, j);
				if (!UnitRef) continue;
				TTRef->SetObjectElementAtIndex(i, j, nullptr);
				TTRef->SetObjectElementAtIndex(i - 1, j, UnitRef);
				UnitRef->SetObjectZandY(i - 1, j);
				int32 UnitZ, UnitY;
				UnitRef->GetObjectZandY(UnitZ, UnitY);
				UnitRef->SetObjectLocation(FVector::ZeroVector, UnitZ, UnitY);
			}
		}
	}
	return true;
}

void ATetrisController::StartMoveDownTimer()
{
	GetWorldTimerManager().ClearTimer(SecondTimerHandle);
	GetWorldTimerManager().SetTimer(SecondTimerHandle, this, &ATetrisController::MoveDownContinously, MoveSpeed, true);
}

void ATetrisController::AddUnitObjectToUnrelatedObjects(TArray<class AObjectUnit*> Array)
{
	for (int32 i = 0; i < Array.Num(); i++)
	{
		UnRelatedObjects.Add(Array[i]);
		Array[i]->MainOwner = nullptr;
	}
}

void ATetrisController::BubleSort(TArray<int32>& Array)
{
	for (int32 i = 0; i < Array.Num() - 1; i++)
	{
		for (int32 j = 0; j < Array.Num() - 1 - i; j++)
		{
			if (Array[j] > Array[j + 1])
			{
				int32 temp = Array[j];
				Array[j] = Array[j + 1];
				Array[j + 1] = temp;
			}
		}
	}
}

void ATetrisController::IncrementMainObjectCounter()
{
	if (MainObjectCounter > 7)
	{
		if (ActiveMoveSpeed > 0.3)
		{
			ActiveMoveSpeed -= 0.05;
			//StartMoveDownTimer();
		}
		MainObjectCounter = 0;
	}

	MainObjectCounter++;
}
