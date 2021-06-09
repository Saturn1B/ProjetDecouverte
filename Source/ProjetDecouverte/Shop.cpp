// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop.h"
#include "Inventory.h"

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
			}
		}
	}

	for (UBuyButton* button : bonusArray)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInventory::StaticClass(), FoundActors);
		AInventory* inventory = Cast<AInventory>(FoundActors[0]);
		for (UBonusSelector* bonus : inventory->bonusSelector)
		{
			if (bonus->index == button->toolIndex)
			{
				button->bonus = bonus;
			}
		}
	}
}

void AShop::ActiveShop()
{
	if(shopPanel->GetVisibility() == ESlateVisibility::Collapsed)
	{
		shopPanel->SetVisibility(ESlateVisibility::Visible);
	}
	else if(shopPanel->GetVisibility() == ESlateVisibility::Visible)
	{
		shopPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
}

