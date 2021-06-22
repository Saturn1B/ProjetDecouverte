// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop.h"
#include "Parametters.h"
#include "Materials.h"
#include "Inventory.h"
#include "AchievmentsTab.h"
#define LOG(fstring) GLog->Log(fstring)

// Sets default values
AShop::AShop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AShop::BeginPlay()
{
	Super::BeginPlay();
	created_ui = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), bp_ui);
	created_ui->AddToViewport();
	shopButton = Cast<UButton>(created_ui->GetWidgetFromName(TEXT("Shop")));
	shopPanel = Cast<UCanvasPanel>(created_ui->GetWidgetFromName(TEXT("ShopPanel")));
	buttonArray.Add(Cast<UBuyButton>(created_ui->GetWidgetFromName(TEXT("BuyButton_1"))));
	buttonArray.Add(Cast<UBuyButton>(created_ui->GetWidgetFromName(TEXT("BuyButton_2"))));
	bonusArray.Add(Cast<UBuyButton>(created_ui->GetWidgetFromName(TEXT("BuyBonus_1"))));
	bonusArray.Add(Cast<UBuyButton>(created_ui->GetWidgetFromName(TEXT("BuyBonus_2"))));
	bonusArray.Add(Cast<UBuyButton>(created_ui->GetWidgetFromName(TEXT("BuyBonus_3"))));

	for (UBuyButton* button : buttonArray)
	{
		button->shop = this;
	}

	//created_ui->SetVisibility(ESlateVisibility::Collapsed);

	shopPanel->SetVisibility(ESlateVisibility::Collapsed);

	shopButton->OnClicked.AddDynamic(this, &AShop::ActiveShop);

	TArray<AActor*> FoundActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATools::StaticClass(), FoundActor);
	for (size_t i = 0; i < FoundActor.Num(); i++)
	{
		toolsArray.Add(Cast<ATools>(FoundActor[i]));
	}

	for (UBuyButton* button : buttonArray)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATools::StaticClass(), FoundActors);
		for (AActor* actorTool : FoundActors)
		{
			ATools* tool = Cast<ATools>(actorTool);
			if (tool->index == button->toolIndex)
			{
				button->tool = tool;
				FString prix = "Prix : ";
				if (button->tool->baseCost[0] > 0)
				{
					prix += FString::FromInt(tool->baseCost[0]) + " fers";
				}
				if (button->tool->baseCost[1] > 0)
				{
					if (prix == "Prix : ")
					{
						prix += FString::FromInt(tool->baseCost[1]) + " bronzes";
					}
					else
					{
						prix += ", " + FString::FromInt(tool->baseCost[1]) + " bronzes";
					}
				}
				if (button->tool->baseCost[2] > 0)
				{
					if (prix == "Prix : ")
					{
						prix += FString::FromInt(tool->baseCost[2]) + " ors";
					}
					else
					{
						prix += ", " + FString::FromInt(tool->baseCost[2]) + " ors";
					}
				}
				if (button->tool->baseCost[3] > 0)
				{
					if (prix == "Prix : ")
					{
						prix += FString::FromInt(tool->baseCost[3]) + " diamants";
					}
					else
					{
						prix += ", " + FString::FromInt(tool->baseCost[3]) + " diamants";
					}
				}
				button->price->SetText(FText::FromString(prix));
			}
		}
	}

	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, this, &AShop::SetButton, 0.1f, false);
}

void AShop::ActiveShop()
{
	inventory->toolInventory->SetVisibility(ESlateVisibility::Collapsed);
	parametters->paramettersPanel->SetVisibility(ESlateVisibility::Collapsed);
	material->matPanel->SetVisibility(ESlateVisibility::Collapsed);
	achievmentsTab->achievments_ui->SetVisibility(ESlateVisibility::Collapsed);
	achievmentsTab->achievmentsPopup->SetVisibility(ESlateVisibility::Collapsed);

	if(shopPanel->GetVisibility() == ESlateVisibility::Collapsed)
	{
		shopPanel->SetVisibility(ESlateVisibility::Visible);
		Tutorisation->ResetPopup();

		parametters->paramettersButton->SetVisibility(ESlateVisibility::Hidden);
		material->matButton->SetVisibility(ESlateVisibility::Hidden);
		achievmentsTab->achieveButton->SetVisibility(ESlateVisibility::Hidden);
	}
	else if(shopPanel->GetVisibility() == ESlateVisibility::Visible)
	{
		shopPanel->SetVisibility(ESlateVisibility::Collapsed);

		parametters->paramettersButton->SetVisibility(ESlateVisibility::Visible);
		material->matButton->SetVisibility(ESlateVisibility::Visible);
		achievmentsTab->achieveButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void AShop::SetButton()
{
	for (UBuyButton* button : bonusArray)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInventory::StaticClass(), FoundActors);
		AInventory* inv = Cast<AInventory>(FoundActors[0]);
		for (UBonusSelector* bonus : inv->bonusSelector)
		{
			LOG("je te deteste");
			if (bonus->index == button->toolIndex)
			{
				button->bonus = bonus;
			}
		}
	}
}

