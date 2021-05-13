// Fill out your copyright notice in the Description page of Project Settings.

#define LOG(fstring) GLog->Log(fstring)
#include "MyPlayerController.h"

// Sets default values
AMyPlayerController::AMyPlayerController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//Visible Component
	/*Visible = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));

	Visible->SetupAttachment(RootComponent);
	Visible->bHiddenInGame = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MyVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));

	if (MyVisualAsset.Succeeded())
	{
		Visible->SetStaticMesh(MyVisualAsset.Object);
	}
	else
	{
		LOG("Loading Failed");
	}*/
}

// Called when the game starts or when spawned
void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MyController = Cast<APlayerController>(GetController());

	if (MyController)
	{
		MyController->bShowMouseCursor = true;
		MyController->bEnableClickEvents = true;
		MyController->bEnableMouseOverEvents = true;
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlanetLayers::StaticClass(), FoundActors);
	for (AActor* layerActor : FoundActors)
	{
		APlanetLayers* layer = Cast<APlanetLayers>(layerActor);
		if (layer->isTopLayer)
		{
			currentLayer = layer;
		}
	}
}

// Called every frame
void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayerController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("LeftClick", IE_Pressed, this, &AMyPlayerController::OnMouseClick);

	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMyPlayerController::OnFingerTouch);
}

void AMyPlayerController::OnMouseClick()
{
	FHitResult HitResult;
	MyController->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, HitResult);

	if (HitResult.GetComponent())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Mouse Click+++ Component: %s"), *HitResult.GetComponent()->GetName()));
	}

	if (HitResult.GetActor())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Mouse Click+++ Actor: %s"), *HitResult.GetActor()->GetName()));
		if (HitResult.GetActor()->GetClass()->IsChildOf(APlanetLayers::StaticClass()))
		{
			Cast<APlanetLayers>(HitResult.GetActor())->LooseHP(1);
		}
	}
}

void AMyPlayerController::OnFingerTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FHitResult HitResult;
	MyController->GetHitResultUnderFinger(ETouchIndex::Type::Touch1, ECollisionChannel::ECC_Pawn, false, HitResult);

	if (HitResult.GetComponent())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Mouse Click+++ Component: %s"), *HitResult.GetComponent()->GetName()));
	}

	if (HitResult.GetActor())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Mouse Click+++ Actor: %s"), *HitResult.GetActor()->GetName()));
		if (HitResult.GetActor()->GetClass()->IsChildOf(APlanetLayers::StaticClass()))
		{
			Cast<APlanetLayers>(HitResult.GetActor())->LooseHP(1);
		}
	}
}

