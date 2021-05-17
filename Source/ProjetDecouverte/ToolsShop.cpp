// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolsShop.h"
#define LOG(fstring) GLog->Log(fstring)

// Sets default values
AToolsShop::AToolsShop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AToolsShop::BeginPlay()
{
	Super::BeginPlay();
	created_ui = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), bp_ui);
	created_ui->AddToViewport();
	toolsButton.Add(Cast<UToolsButton>(created_ui->GetWidgetFromName(TEXT("ToolsButton_1"))));

	TArray<AActor*> FoundMaterials;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMaterials::StaticClass(), FoundMaterials);

	for (UToolsButton* button : toolsButton)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAutomaticTools::StaticClass(), FoundActors);
		for (AActor* actorTool : FoundActors)
		{
			AAutomaticTools* tool = Cast<AAutomaticTools>(actorTool);
			if (tool->Index == button->index)
			{
				button->tool = tool;
				button->materials = Cast<AMaterials>(FoundMaterials[0]);
			}
		}
	}
}

// Called every frame
void AToolsShop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

