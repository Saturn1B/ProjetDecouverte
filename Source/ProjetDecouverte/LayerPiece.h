// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tutorisation.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LayerPiece.generated.h"

class UNiagaraSystem;
class AMyPlayerController2;

UCLASS()
class PROJETDECOUVERTE_API ALayerPiece : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALayerPiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class APlayerController* MyController;

	UPROPERTY(editanywhere)
		UStaticMeshComponent* Visible;

	UPROPERTY(editanywhere)
		class ALayerPiece* lavaPiece;

	UPROPERTY(editanywhere)
		class AActor* Planet;

	UPROPERTY(editanywhere)
		TArray<AActor*> FoundChildren;

	UPROPERTY(editanywhere)
		int LayerHp;

	UPROPERTY(editanywhere)
		int PieceHP;

		int HP;

	float HPMultiplier;

	UPROPERTY(editanywhere)
		float strength;

	void LooseHP(int damageValue, FVector destroyLoc);
	void Kill();
	void DestroyPiece(int i);

	//Bool type

	UPROPERTY(editanywhere)
		bool liquid;

	UPROPERTY(editanywhere)
		bool indestructible;

	UPROPERTY(editanywhere)
		bool lava;

	UPROPERTY(editanywhere)
		bool core;

	//if lava

	void LavaSpread();

	UPROPERTY(editanywhere)
		TArray<class ALayerPiece*> spreadPieces;

	//material given

	UPROPERTY(editanywhere)
		int minMat;

	UPROPERTY(editanywhere)
		int maxMat;

	UPROPERTY(editanywhere)
		int matIndex;

	UPROPERTY(editanywhere)
		UMaterialInterface* coreMat;

	UMaterialInstanceDynamic* dynamicMaterial;

	UPROPERTY(editanywhere)
		UMaterialInstance* indestructibleMat;

	//camera shake

	UPROPERTY(editanywhere)
		TSubclassOf<UMatineeCameraShake> CamShakeSmall;

	UPROPERTY(editanywhere)
		TSubclassOf<UMatineeCameraShake> CamShakeBig;

	//haptic

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UForceFeedbackEffect* haptic1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UForceFeedbackEffect* haptic2;

	//fx

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UNiagaraSystem* TouchVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UNiagaraSystem* DestroyVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMyPlayerController2* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ATutorisation* Tutorisation;

	//sound

	UPROPERTY(editanywhere, Category = "Sound")
		TArray<USoundBase*> pickaxeSound;
	UPROPERTY(editanywhere, Category = "Sound")
		TArray<USoundBase*> explosionSound;
	UPROPERTY(editanywhere, Category = "Sound")
		USoundBase* liquidSound;
};
