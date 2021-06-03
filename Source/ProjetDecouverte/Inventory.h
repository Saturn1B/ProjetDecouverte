// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "ToolSelector.h"
#include "Inventory.generated.h"

class ToolSelector;
class Materials;

UCLASS()
class PROJETDECOUVERTE_API AInventory : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInventory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(editanywhere)
		TSubclassOf<UUserWidget> bp_ui;

	UPROPERTY(editanywhere)
		UUserWidget* created_ui;

	UPROPERTY(editanywhere)
		TArray<class UToolSelector*> toolSelector;

	UPROPERTY(editanywhere)
		class UCanvasPanel* toolInventory;

	UPROPERTY(editanywhere)
		class UButton* invButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMaterials* materials;

	UFUNCTION()
		void ShowToolInv();
};
