// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Tutorisation.generated.h"

UCLASS()
class PROJETDECOUVERTE_API ATutorisation : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATutorisation();

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
		class UBorder* popup;

	UPROPERTY(editanywhere)
		class UImage* popupImage;

	UPROPERTY(editanywhere)
		class UTextBlock* popupText;

	UPROPERTY(editanywhere)
		class UTexture2D* ressource;
	UPROPERTY(editanywhere)
		class UTexture2D* mission;
	UPROPERTY(editanywhere)
		class UTexture2D* shop;
	UPROPERTY(editanywhere)
		class UTexture2D* inventory;

	void SetPopup(FString text, float time, UTexture2D* image);
	void ResetPopup();
};
