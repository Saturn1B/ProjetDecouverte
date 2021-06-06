// Fill out your copyright notice in the Description page of Project Settings.


#include "BuyButton.h"
#include "Shop.h"
#include "Tools.h"
#include "Inventory.h"
#define LOG(fstring) GLog->Log(fstring)

UBuyButton::UBuyButton()
{
	OnClicked.AddDynamic(this, &UBuyButton::Clicked);
}

void UBuyButton::Clicked()
{
	if (!bonus)
	{
		if (tool->upgradeIndex == 0)
		{
			tool->Buy();
			text->SetText(FText::FromString("UP"));
		}
		else
		{
			tool->Upgrade();
			text->SetText(FText::FromString("UP"));
		}

	}
	else
	{
		TArray<AActor*> FoundInventory;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInventory::StaticClass(), FoundInventory);
		AInventory* inventory = Cast<AInventory>(FoundInventory[0]);
		for (UBonusSelector* selector : inventory->bonusSelector)
		{
			if (toolIndex == selector->index)
			{
				selector->SetIsEnabled(true);
				this->SetIsEnabled(false);
			}
		}
	}
}
