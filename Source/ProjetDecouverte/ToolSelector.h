// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "ToolSelector.generated.h"

class Inventory;
class Tools;
class MyPlayerController2;

/**
 *
 */
UCLASS()
class PROJETDECOUVERTE_API UToolSelector : public UButton
{
	GENERATED_BODY()

public :

	UToolSelector();

	UPROPERTY(editanywhere)
		int toolIndex;

	UPROPERTY(editanywhere)
		class ATools* tool;

	UFUNCTION(BlueprintCallable)
		void Clicked();

	UPROPERTY(editanywhere)
		class AInventory* inventory;

	UPROPERTY(editanywhere, Category = "Sound")
		USoundBase* selectSound;
};
