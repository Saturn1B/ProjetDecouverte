// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "AutomaticTools.h"
#include "Kismet/GameplayStatics.h"
#include "ToolsButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJETDECOUVERTE_API UToolsButton : public UButton
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
		void BuyTool();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int index;
};
