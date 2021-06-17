// Fill out your copyright notice in the Description page of Project Settings.


#include "Materials.h"
#include "Parametters.h"
#include "Shop.h"
#include "Inventory.h"
#include "AchievmentsTab.h"
#define LOG(fstring) GLog->Log(fstring)

// Sets default values
AMaterials::AMaterials()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMaterials::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShop::StaticClass(), FoundActor);
	shop = Cast<AShop>(FoundActor[0]);

	created_ui = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), bp_ui);
	created_ui->AddToViewport();

	matPanel = Cast<UCanvasPanel>(created_ui->GetWidgetFromName(TEXT("Materials")));
	matButton = Cast<UButton>(created_ui->GetWidgetFromName(TEXT("Button_1")));
	backButton = Cast<UButton>(created_ui->GetWidgetFromName(TEXT("Button_2")));

	matPanel->SetVisibility(ESlateVisibility::Collapsed);

	materialsText.Add(Cast<UTextBlock>(created_ui->GetWidgetFromName(TEXT("MatNumber_1"))));
	materialsCount.Add(0);
	materialsText[0]->SetText(FText::FromString(FString::FromInt(materialsCount[0])));

	materialsText.Add(Cast<UTextBlock>(created_ui->GetWidgetFromName(TEXT("MatNumber_2"))));
	materialsCount.Add(0);
	materialsText[1]->SetText(FText::FromString(FString::FromInt(materialsCount[0])));

	materialsText.Add(Cast<UTextBlock>(created_ui->GetWidgetFromName(TEXT("MatNumber_3"))));
	materialsCount.Add(0);
	materialsText[2]->SetText(FText::FromString(FString::FromInt(materialsCount[0])));

	materialsText.Add(Cast<UTextBlock>(created_ui->GetWidgetFromName(TEXT("MatNumber_4"))));
	materialsCount.Add(0);
	materialsText[3]->SetText(FText::FromString(FString::FromInt(materialsCount[0])));

	materialsText.Add(Cast<UTextBlock>(created_ui->GetWidgetFromName(TEXT("MatNumber_5"))));
	materialsCount.Add(0);
	materialsText[4]->SetText(FText::FromString(FString::FromInt(materialsCount[0])));

	matButton->OnClicked.AddDynamic(this, &AMaterials::MatTab);
	backButton->OnClicked.AddDynamic(this, &AMaterials::MatTab);

	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, this, &AMaterials::CheckMat, 0.2f, false);
}

void AMaterials::UpdateMaterial(int index, int value)
{
	materialsCount[index] += value;
	materialsText[index]->SetText(FText::FromString(FString::FromInt(materialsCount[index])));

	for (UBuyButton* button : shop->buttonArray)
	{
		button->SetIsEnabled(true);
		for (size_t i = 0; i < materialsCount.Num(); i++)
		{
			if (button->tool->currentCost[i] > materialsCount[i])
			{
				button->SetIsEnabled(false);
			}
		}
	}

	for (UBuyButton* button : shop->bonusArray)
	{
		if(!button->isBought)
		{
			button->SetIsEnabled(true);
			for (size_t i = 0; i < materialsCount.Num(); i++)
			{
				if (button->bonus->cost[i] > materialsCount[i])
				{
					button->SetIsEnabled(false);
				}
			}
		}
	}
}

void AMaterials::CheckMat()
{
	for (UBuyButton* button : shop->buttonArray)
	{
		button->SetIsEnabled(true);
		LOG(FString::FromInt(materialsCount.Num()));
		for (size_t i = 0; i < materialsCount.Num(); i++)
		{
			LOG(FString::FromInt(button->tool->baseCost[i]));
			LOG(FString::FromInt(materialsCount[i]));
			if (button->tool->baseCost[i] > materialsCount[i])
			{
				button->SetIsEnabled(false);
			}
		}
	}

	for (UBuyButton* button : shop->bonusArray)
	{
		button->SetIsEnabled(true);
		LOG(FString::FromInt(materialsCount.Num()));
		for (size_t i = 0; i < materialsCount.Num(); i++)
		{
			LOG(FString::FromInt(button->bonus->cost[i]));
			LOG(FString::FromInt(materialsCount[i]));
			if (button->bonus->cost[i] > materialsCount[i])
			{
				button->SetIsEnabled(false);
			}
		}
	}
}

void AMaterials::MatTab()
{
	matUse += 1;

	if (matUse == 2)
	{
		Tutorisation->ResetPopup();
		FString text = "C'est pas beaucoup de ressources! Il te faut peut etre un peu plus de motivation. Va dans l'onglet mission pour en trouver";
		Tutorisation->SetPopup(text, 12.0f, 2);
	}

	if (matPanel->GetVisibility() == ESlateVisibility::Collapsed)
	{
		matPanel->SetVisibility(ESlateVisibility::Visible);
		matButton->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		matPanel->SetVisibility(ESlateVisibility::Collapsed);
		matButton->SetVisibility(ESlateVisibility::Visible);
	}

	inventory->toolInventory->SetVisibility(ESlateVisibility::Collapsed);
	shop->shopPanel->SetVisibility(ESlateVisibility::Collapsed);
	shop->shopButton->SetVisibility(ESlateVisibility::Visible);
	parametters->paramettersPanel->SetVisibility(ESlateVisibility::Collapsed);
	parametters->paramettersButton->SetVisibility(ESlateVisibility::Visible);
	achievmentsTab->achievments_ui->SetVisibility(ESlateVisibility::Collapsed);
	achievmentsTab->achieveButton->SetVisibility(ESlateVisibility::Visible);
	achievmentsTab->achievmentsPopup->SetVisibility(ESlateVisibility::Collapsed);
}

