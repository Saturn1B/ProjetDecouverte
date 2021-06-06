// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "ToolSelector.h"
#include "BonusSelector.h"
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
	toolSelector.Add(Cast<UToolSelector>(created_ui->GetWidgetFromName(TEXT("ToolInvButton_2"))));

	bonusSelector.Add(Cast<UBonusSelector>(created_ui->GetWidgetFromName(TEXT("BonusInvButton_1"))));
	bonusSelector.Add(Cast<UBonusSelector>(created_ui->GetWidgetFromName(TEXT("BonusInvButton_2"))));

	invButton->OnClicked.AddDynamic(this, &AInventory::ShowToolInv);

	toolInventory->SetVisibility(ESlateVisibility::Collapsed);

	TArray<AActor*> FoundActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATools::StaticClass(), FoundActor);
	for (size_t i = 0; i < FoundActor.Num(); i++)
	{
		toolsArray.Add(Cast<ATools>(FoundActor[i]));
	}

	for (UToolSelector* selector : toolSelector)
	{
		selector->inventory = this;
		for (ATools* tool : toolsArray)
		{
			if (tool->index == selector->toolIndex)
			{
				selector->tool = tool;
			}
		}
		if (!selector->tool->isActive)
		{
			selector->SetIsEnabled(false);
		}
	}

	for (UBonusSelector* selector : bonusSelector)
	{
		selector->SetIsEnabled(false);
	}

	materials->materialsText.Add(Cast<UTextBlock>(created_ui->GetWidgetFromName(TEXT("MatNumber_1"))));
	materials->materialsCount.Add(0);
	materials->materialsText[0]->SetText(FText::FromString(FString::FromInt(materials->materialsCount[0])));

	//created_ui->SetVisibility(ESlateVisibility::Visible);
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

