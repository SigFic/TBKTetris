// Fill out your copyright notice in the Description page of Project Settings.


#include "MainObject.h"
#include "ObjectUnit.h"
#include "TetrisController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainObject::AMainObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ObjectCounter = 0;
}

void AMainObject::DecrementObjectCounter()
{
	if (ObjectCounter > 1)
	{
		ObjectCounter--;
	}

	else if (ObjectCounter <= 1)
	{
		Destroy();
	}
}

// Called when the game starts or when spawned
void AMainObject::BeginPlay()
{
	Super::BeginPlay();

	Objects.SetNum(ObjectCounter);

	ATetrisController* TCRef = Cast<ATetrisController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!TCRef) return;

	TArray<AObjectUnit*> FreeObjects = TCRef->GetObjects(ObjectCounter);

	for (int32 i = 0; i < ObjectCounter; i++)
	{
		AObjectUnit* ObjectRef = FreeObjects[i];
		if (ObjectRef)
		{
			ObjectRef->bIsMovingRightNow = true;
			Objects[i] = ObjectRef;
			ObjectRef->MainOwner = this;
		}
	}
	
}

// Called every frame
void AMainObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AMainObject::MoveLeft()
{
	for (int32 i = 0; i < ObjectCounter; i++)
	{
		if (!Objects[i]->CheckifObjectCanMoveSide(false)) return false;
	}

	for (int32 i = 0; i < ObjectCounter; i++)
	{
		int32 ActiveZ, ActiveY;
		Objects[i]->GetObjectZandY(ActiveZ, ActiveY);
		Objects[i]->SetObjectZandY(ActiveZ, ActiveY - 1);
		Objects[i]->GetObjectZandY(ActiveZ, ActiveY);
		Objects[i]->SetObjectLocation(FVector::ZeroVector, ActiveZ, ActiveY);
	}

	return true;
}

bool AMainObject::MoveRight()
{
	for (int32 i = 0; i < ObjectCounter; i++)
	{
		if (!Objects[i]->CheckifObjectCanMoveSide(true)) return false;
	}

	for (int32 i = 0; i < ObjectCounter; i++)
	{
		int32 ActiveZ, ActiveY;
		Objects[i]->GetObjectZandY(ActiveZ, ActiveY);
		Objects[i]->SetObjectZandY(ActiveZ, ActiveY + 1);
		Objects[i]->GetObjectZandY(ActiveZ, ActiveY);
		Objects[i]->SetObjectLocation(FVector::ZeroVector, ActiveZ, ActiveY);
	}

	return true;
}

bool AMainObject::MoveDown()
{
	for (int32 i = 0; i < ObjectCounter; i++)
	{
		if (!Objects[i]->CheckifObjectCanMoveDown()) return false;
	}

	for (int32 i = 0; i < ObjectCounter; i++)
	{
		int32 ActiveZ, ActiveY;
		Objects[i]->GetObjectZandY(ActiveZ, ActiveY);
		Objects[i]->SetObjectZandY(ActiveZ - 1, ActiveY);
		Objects[i]->GetObjectZandY(ActiveZ, ActiveY);
		Objects[i]->SetObjectLocation(FVector::ZeroVector, ActiveZ, ActiveY);
	}

	return true;
}

bool AMainObject::Rotate()
{
	for (int32 i = 0; i < ObjectCounter; i++)
	{
		int32 ActiveZ, ActiveY, NewZ, NewY;
		Objects[0]->GetObjectZandY(ActiveZ, ActiveY);

		if (Objects[i]->CheckifObjectCanTurn(ActiveZ, ActiveY, NewZ, NewY))
		{
			FVector2D ZandY;
			ZandY.X = NewZ;
			ZandY.Y = NewY;
			ObjectToNewLocation.Add(Objects[i], ZandY);
		}

		else
		{
			ObjectToNewLocation.Reset();
			return false;
		}
	}

	for (int32 i = 0; i < ObjectCounter; i++)
	{
		int32 ActiveZ, ActiveY;
		FVector2D* ZandY = ObjectToNewLocation.Find(Objects[i]);
		ActiveZ = ZandY->X;
		ActiveY = ZandY->Y;
		Objects[i]->SetObjectZandY(ActiveZ, ActiveY);
		Objects[i]->SetObjectLocation(FVector::ZeroVector, ActiveZ, ActiveY);
	}

	return true;
}





