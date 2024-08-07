// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TetrisGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_API ATetrisGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ATetrisGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris Table ")
	class UTetrisTable* TetrisTableInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris Table")
	TSubclassOf<UTetrisTable> TetrisClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerController")
	TSubclassOf<APlayerController> ControllerClass;
protected:

	virtual void BeginPlay() override;



};
