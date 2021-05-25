// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "AutomaticTools.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "ToolsUse.generated.h"

/**
 * 
 */
UCLASS()
class PROJETDECOUVERTE_API UToolsUse : public UButton
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		void UseTool();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTextBlock* ButtonTextState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AAutomaticTools* tool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int index = 0;
	
};
