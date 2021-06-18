// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LayerPiece.h"
#include "Planet.h"
#include "SolarSystem.h"
#include "Tools.h"
#include "Materials.h"
#include "Shop.h"
#include "Inventory.h"
#include "Materials/MaterialInterface.h"
#include "Components/AudioComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController2.generated.h"

class UNiagaraSystem;

UCLASS()
class PROJETDECOUVERTE_API AMyPlayerController2 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPlayerController2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class APlayerController* MyController;

	void OnFingerTouch(const ETouchIndex::Type FingerIndex, const FVector Location);

	void OnFingerRelease(const ETouchIndex::Type FingerIndex, const FVector Location);

	void OnFingerPinch(float AxisValue);

	void HoldDamage(class ALayerPiece* layerPiece);

	void HidePlanet();

	void ShowPlanet();

	float pinchDelta;
	float currentPinch;
	float previousPinch;

	/*UPROPERTY(editanywhere)
		UStaticMeshComponent* Visible;*/

	UPROPERTY(editanywhere)
		class ATools* currentTool;

	UPROPERTY(editanywhere)
		class AActor* ObjectSelected;

	UPROPERTY(editanywhere)
		class AActor* Camera;

	UPROPERTY(editanywhere)
		int PlanetSelected;

	UPROPERTY(editanywhere)
		float damageBonus = 1;

	UPROPERTY(editanywhere)
		float materialBonus = 1;

	UPROPERTY(editanywhere)
		TArray<class AActor*> Planets;

	UPROPERTY(editanywhere)
		bool onDrag;

	UPROPERTY(editanywhere)
		bool clickHold;

	UPROPERTY(editanywhere)
		bool zoomedOut;

	UPROPERTY(editanywhere)
		bool tuto1 = false;

	UPROPERTY(editanywhere)
		FVector2D currentTouch;

	UPROPERTY(editanywhere)
		FVector2D previousTouch;

	UPROPERTY(editanywhere)
		FRotator MouseRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMaterials* materials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AShop* shop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AInventory* inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UForceFeedbackEffect* haptic1;

	UPROPERTY(editanywhere, Category = "Sound")
		USoundBase* holdSound;
	//UPROPERTY(editanywhere, Category = "Sound")
		UAudioComponent* holdSoundComponent;
};
