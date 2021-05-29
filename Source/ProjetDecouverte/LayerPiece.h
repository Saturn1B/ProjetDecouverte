// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LayerPiece.generated.h"

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

	UPROPERTY(editanywhere)
		UStaticMeshComponent* Visible;

	UPROPERTY(editanywhere)
		class ALayerPiece* lavaPiece;

	UPROPERTY(editanywhere)
		int HP;

	UPROPERTY(editanywhere)
		float strength;

	void LooseHP(int damageValue);
	void Kill();

	UPROPERTY(editanywhere)
		TArray<int> materialsIndex;

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

};
