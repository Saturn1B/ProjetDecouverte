// Fill out your copyright notice in the Description page of Project Settings.

#define LOG(fstring) GLog->Log(fstring)
#include "PlanetLayers.h"

// Sets default values
APlanetLayers::APlanetLayers()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//Visible Component
	Visible = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));

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
	}
}

// Called when the game starts or when spawned
void APlanetLayers::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlanetLayers::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlanetLayers::LooseHP(int damageValue)
{
	HP -= damageValue;
	if (HP <= 0)
	{
		if (NextLayer != NULL)
		{
			NextLayer->isTopLayer = true;
			TArray<AActor*> FoundActors1;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAutomaticTools::StaticClass(), FoundActors1);
			for (AActor* tool : FoundActors1)
			{
				Cast<AAutomaticTools>(tool)->currentLayer = NextLayer;
			}
			TArray<AActor*> FoundActors2;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPlayerController::StaticClass(), FoundActors2);
			Cast<AMyPlayerController>(FoundActors2[0])->currentLayer = NextLayer;
		}
		else 
		{
			TArray<AActor*> FoundActors1;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAutomaticTools::StaticClass(), FoundActors1);
			for (AActor* tool : FoundActors1)
			{
				Cast<AAutomaticTools>(tool)->currentLayer = NULL;
			}
			TArray<AActor*> FoundActors2;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPlayerController::StaticClass(), FoundActors2);
			Cast<AMyPlayerController>(FoundActors2[0])->currentLayer = NULL;
		}

		Destroy();
	}
}

