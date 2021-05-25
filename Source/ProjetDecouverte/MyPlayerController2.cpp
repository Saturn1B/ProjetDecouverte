// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController2.h"
#define LOG(fstring) GLog->Log(fstring)

// Sets default values
AMyPlayerController2::AMyPlayerController2()
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
void AMyPlayerController2::BeginPlay()
{
	Super::BeginPlay();
	
	MyController = Cast<APlayerController>(GetController());

	if (MyController)
	{
		MyController->bShowMouseCursor = true;
		MyController->bEnableClickEvents = true;
		MyController->bEnableMouseOverEvents = true;
	}

	TArray<AActor*> FoundMaterials;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMaterials::StaticClass(), FoundMaterials);
	materials = Cast<AMaterials>(FoundMaterials[0]);

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlanet::StaticClass(), Planets);
	PlanetSelected = 0;
}

// Called every frame
void AMyPlayerController2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//MyController->GetInputMouseDelta(mouseX, mouseY);

	MyController->GetInputTouchState(ETouchIndex::Touch1, currentTouch.X, currentTouch.Y, onDrag);

	FVector2D deltaTouch;

	if (onDrag) 
	{
		deltaTouch = currentTouch - previousTouch;

		previousTouch = currentTouch;
	}

	MouseRotation = FRotator(deltaTouch.Y, deltaTouch.X, 0) * 0.1;

	//Un objet est séléctionné est peut donc être manipulé
	if (ObjectSelected != NULL)
	{
		if (!zoomedOut)
		{
			//Pour pouvoir bouger dans tous les sens l'objet séléctioné
			APlanet* Planet = Cast<APlanet>(ObjectSelected);
			Planet->PlanetRotation.Yaw -= MouseRotation.Yaw;
			Planet->PlanetRotation.Pitch += MouseRotation.Pitch;

			ObjectSelected->SetActorRotation(Planet->PlanetRotation, ETeleportType::None);
		}
		else
		{
			if (deltaTouch.Y >= 4)
			{
				ASolarSystem* System = Cast<ASolarSystem>(ObjectSelected);
				System->SystemRotation.Yaw += 90;

				if (PlanetSelected + 1 < Planets.Num())
				{
					PlanetSelected += 1;
				}
				else
				{
					PlanetSelected = 0;
				}

				ObjectSelected->SetActorRotation(System->SystemRotation, ETeleportType::None);
				ObjectSelected = NULL;
			}
			else if (deltaTouch.Y <= -4)
			{
				ASolarSystem* System = Cast<ASolarSystem>(ObjectSelected);
				System->SystemRotation.Yaw -= 90;

				if (PlanetSelected - 1 >= 0)
				{
					PlanetSelected -= 1;
				}
				else
				{
					PlanetSelected = Planets.Num() - 1;
				}

				ObjectSelected->SetActorRotation(System->SystemRotation, ETeleportType::None);
				ObjectSelected = NULL;
			}
		}
	}
}

// Called to bind functionality to input
void AMyPlayerController2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("LeftClick", IE_Pressed, this, &AMyPlayerController2::OnMouseClick);

	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMyPlayerController2::OnFingerTouch);

	InputComponent->BindTouch(EInputEvent::IE_Released, this, &AMyPlayerController2::OnFingerRelease);

	//InputComponent->BindGesture(EGestureEvent::, this, &AMyPlayerController2::OnFingerRelease);
}

void AMyPlayerController2::OnMouseClick()
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
		if (HitResult.GetActor()->GetClass()->IsChildOf(ALayerPiece::StaticClass()))
		{
			Cast<ALayerPiece>(HitResult.GetActor())->LooseHP(1);
		}
	}
}

void AMyPlayerController2::OnFingerTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	MyController->GetInputTouchState(ETouchIndex::Touch1, previousTouch.X, previousTouch.Y, onDrag);
	onDrag = true;

	if (!zoomedOut)
	{
		FHitResult HitResult;
		MyController->GetHitResultUnderFinger(ETouchIndex::Type::Touch1, ECollisionChannel::ECC_Pawn, false, HitResult);

		if (HitResult.GetActor())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Mouse Click+++ Actor: %s"), *HitResult.GetActor()->GetName()));
			if (HitResult.GetActor()->GetClass()->IsChildOf(ALayerPiece::StaticClass()))
			{
				if (Cast<ALayerPiece>(HitResult.GetActor())->HP > 0)
				{
					Cast<ALayerPiece>(HitResult.GetActor())->LooseHP(1);

					for (size_t i = 0; i < Cast<ALayerPiece>(HitResult.GetActor())->materialsIndex.Num(); i++)
					{
						materials->UpdateMaterial(Cast<ALayerPiece>(HitResult.GetActor())->materialsIndex[i], 1);
					}

					TArray<AActor*> FoundActors2;
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAutomaticTools::StaticClass(), FoundActors2);
					for (AActor* toolActor : FoundActors2)
					{
						Cast<AAutomaticTools>(toolActor)->currentPiece = Cast<ALayerPiece>(HitResult.GetActor());
						/*if (Cast<AAutomaticTools>(toolActor)->isActive)
						{
							Cast<AAutomaticTools>(toolActor)->Mine();
						}*/
					}
				}
				ObjectSelected = Planets[PlanetSelected];
			}
		}
	}
	else
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASolarSystem::StaticClass(), FoundActors);
		ObjectSelected = FoundActors[0];
	}
}

void AMyPlayerController2::OnFingerRelease(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	ObjectSelected = NULL;
	onDrag = false;
	currentTouch = FVector2D(0, 0);
	previousTouch = FVector2D(0, 0);
	MouseRotation = FRotator(0, 0, 0);
}

