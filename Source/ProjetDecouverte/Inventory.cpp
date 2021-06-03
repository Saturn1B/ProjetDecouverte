// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "ToolSelector.h"
#include "Materials.h"

// Sets default values
AInventory::AInventory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInventory::BeginPlay()
{
	Super::BeginPlay();

	created_ui = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), bp_ui);
	created_ui->AddToViewport();

	toolInventory = Cast<UCanvasPanel>(created_ui->GetWidgetFromName(TEXT("ToolPanel")));
	invButton = Cast<UButton>(created_ui->GetWidgetFromName(TEXT("InvButton")));
	toolSelector.Add(Cast<UToolSelector>(created_ui->GetWidgetFromName(TEXT("ToolInvButton_1"))));

	invButton->OnClicked.AddDynamic(this, &AInventory::ShowToolInv);

	toolInventory->SetVisibility(ESlateVisibility::Collapsed);

	for (UToolSelector* selector : toolSelector)
	{
		selector->inventory = this;
	}

	materials->materialsText.Add(Cast<UTextBlock>(created_ui->GetWidgetFromName(TEXT("MatNumber_1"))));
	materials->materialsCount.Add(0);

	created_ui->SetVisibility(ESlateVisibility::Visible);
}

// Called every frame
void AInventory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInventory::ShowToolInv()
{
	if (toolInventory->Visibility == ESlateVisibility::Collapsed)
	{
		toolInventory->SetVisibility(ESlateVisibility::Visible);
	}
	else if (toolInventory->Visibility == ESlateVisibility::Visible)
	{
		toolInventory->SetVisibility(ESlateVisibility::Collapsed);
	}
}

