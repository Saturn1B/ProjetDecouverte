// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController2.h"
#include "ToolSelector.generated.h"

class Inventory;
class Tools;

/**
 *
 */
UCLASS()
class PROJETDECOUVERTE_API UToolSelector : public UButton
{
	GENERATED_BODY()

public :

	UPROPERTY(editanywhere)
		int toolIndex;

	UFUNCTION(BlueprintCallable)
		void Clicked();

	UPROPERTY(editanywhere)
		class AInventory* inventory;
};
