// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisGameMode.h"
#include "TetrisTable.h"

ATetrisGameMode::ATetrisGameMode()
{
	if (ControllerClass)
	{
		PlayerControllerClass = ControllerClass;
	}
}

void ATetrisGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (!TetrisTableInstance)
	{
		TetrisTableInstance = NewObject<UTetrisTable>(this, TetrisClass );
	}
}
