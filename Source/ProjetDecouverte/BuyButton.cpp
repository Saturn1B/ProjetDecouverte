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
	if (!isBonus)
	{
		if (tool->upgradeIndex == 0)
		{
			tool->Buy();
			text->SetText(FText::FromString("UP"));
			/*if (toolIndex == 1)
			{
				TArray<AActor*> FoundTuto;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATutorisation::StaticClass(), FoundTuto);
				Tutorisation = Cast<ATutorisation>(FoundTuto[0]);

				Tutorisation->ResetPopup();
				FString textTuto = "Voila une bonne chose de faite! Tu pourra aussi les améliorer quand t'aura plus de ressource. Pour l'instant retourne sur la planète et va dans ton inventaire pour équiper ton nouvel outil. C'est aussi ici que tu pourra utiliser tes boosts (enfin, quand t'en aura)";
				Tutorisation->SetPopup(textTuto, 20.0f, Tutorisation->inventory);
			}*/
		}
		else
		{
			tool->Upgrade();
			text->SetText(FText::FromString("UP"));
		}

	}
	else
	{
		//TArray<AActor*> FoundInventory;
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInventory::StaticClass(), FoundInventory);
		//AInventory* inventory = Cast<AInventory>(FoundInventory[0]);
		//for (UBonusSelector* selector : inventory->bonusSelector)
		//{
			//if (toolIndex == bonus->index)
			//{
		isBought = true;
		bonus->SetIsEnabled(true);
		this->SetIsEnabled(false);
			//}
		//}
	}
}
