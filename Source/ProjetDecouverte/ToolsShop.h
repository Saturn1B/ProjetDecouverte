// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Components/Button.h"
#include "ToolsButton.h"
#include "ToolsActivation.h"
#include "ToolsUse.h"
#include "AutomaticTools.h"
#include "Materials.h"
#include "MyPlayerController2.h"
#include "ToolsShop.generated.h"

UCLASS()
class PROJETDECOUVERTE_API AToolsShop : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AToolsShop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(editanywhere)
		TArray<class UToolsButton*> toolsButton;

	UPROPERTY(editanywhere)
		TArray<class UToolsActivation*> toolsActivation;

	UPROPERTY(editanywhere)
		TSubclassOf<UUserWidget> bp_ui;

	UPROPERTY(editanywhere)
		UUserWidget* created_ui;

	UPROPERTY(editanywhere)
		class UButton* mapButton;

	UPROPERTY(editanywhere)
		class AActor* camera;

	UFUNCTION()
		void ZoomInOut();
};
