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

	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Camera")), FoundCameras);
	Camera = FoundCameras[0];

	//TArray<AActor*> FoundPlanets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlanet::StaticClass(), Planets);
	bool sorted = false;
	AActor* temp;
	while (!sorted)
	{
		sorted = true;
		for (size_t i = 0; i < Planets.Num() - 1; i++)
		{
			if (Cast<APlanet>(Planets[i])->Index > Cast<APlanet>(Planets[i + 1])->Index)
			{
				temp = Planets[i];
				Planets[i] = Planets[i + 1];
				Planets[i + 1] = temp;
				sorted = false;
			}
		}
	}

	PlanetSelected = 0;

	TArray<AActor*> FoundTools;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATools::StaticClass(), FoundTools);
	for(AActor* actorTool : FoundTools)
	{
		if(Cast<ATools>(actorTool)->index == 0)
		{
			currentTool = Cast<ATools>(actorTool);
		}
	}
	currentTool->isActive = true;
	currentTool->upgradeIndex += 1;
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

	if(deltaTouch.X >= 2 || deltaTouch.Y >= 2)
	{
		clickHold = false;
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

	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMyPlayerController2::OnFingerTouch);

	InputComponent->BindTouch(EInputEvent::IE_Released, this, &AMyPlayerController2::OnFingerRelease);

	InputComponent->BindAxis("UnZoom", this, &AMyPlayerController2::OnFingerPinch);

	//InputComponent->BindGesture(EGestureEvent::, this, &AMyPlayerController2::OnFingerRelease);
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
			if (HitResult.GetActor()->GetClass()->IsChildOf(ALayerPiece::StaticClass()))
			{
				if (Cast<ALayerPiece>(HitResult.GetActor())->HP > 0 && !Cast<ALayerPiece>(HitResult.GetActor())->indestructible && !Cast<ALayerPiece>(HitResult.GetActor())->lava)
				{
					if(!currentTool->onHold)
					{
						if(Cast<ALayerPiece>(HitResult.GetActor())->liquid == currentTool->onLiquid)
						{
							Cast<ALayerPiece>(HitResult.GetActor())->LooseHP(currentTool->currentDamage);
						}
					}
					else
					{
						if (Cast<ALayerPiece>(HitResult.GetActor())->liquid == currentTool->onLiquid)
						{
							clickHold = true;
							HoldDamage(Cast<ALayerPiece>(HitResult.GetActor()));
						}
					}

					/*for (size_t i = 0; i < Cast<ALayerPiece>(HitResult.GetActor())->materialsIndex.Num(); i++)
					{
						materials->UpdateMaterial(Cast<ALayerPiece>(HitResult.GetActor())->materialsIndex[i], 1);
					}*/
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
	clickHold = false;
	currentTouch = FVector2D(0, 0);
	previousTouch = FVector2D(0, 0);
	MouseRotation = FRotator(0, 0, 0);
	currentPinch = 0;
	previousPinch = 0;
	pinchDelta = 0;
}

void AMyPlayerController2::OnFingerPinch(float AxisValue)
{
	previousPinch = currentPinch;
	currentPinch = AxisValue;
	pinchDelta = currentPinch - previousPinch;
	if(pinchDelta > 1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ZoomPinch %f"), pinchDelta));
		if (zoomedOut)
		{
			Camera->SetActorLocation(FVector(Camera->GetActorLocation().X, Camera->GetActorLocation().Y, 70));
			zoomedOut = false;
		}
	}
	else if(pinchDelta < -1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ZoomPinch %f"), pinchDelta));
		if(!zoomedOut)
		{
			Camera->SetActorLocation(FVector(Camera->GetActorLocation().X, Camera->GetActorLocation().Y, 170));
			zoomedOut = true;
		}
	}
}

void AMyPlayerController2::HoldDamage(class ALayerPiece* layerPiece)
{
	if (clickHold)
	{
		layerPiece->LooseHP(currentTool->currentDamage);
		FTimerHandle handle;
		FTimerDelegate HoldDamageDel;
		HoldDamageDel.BindUFunction(this, FName("HoldDamage"), layerPiece);
		GetWorldTimerManager().SetTimer(handle, HoldDamageDel, currentTool->holdTimer, false);
	}
}

