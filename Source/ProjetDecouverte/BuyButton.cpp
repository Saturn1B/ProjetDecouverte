// Fill out your copyright notice in the Description page of Project Settings.


#include "BuyButton.h"
#include "Shop.h"
#include "Tools.h"
#include "Inventory.h"
#define LOG(fstring) GLog->Log(fstring)

UBuyButton::UBuyButton()
{
	OnClicked.AddDynamic(this, &UBuyButton::Clicked);
	static ConstructorHelpers::FObjectFinder<USoundBase> MyAudioAsset1(TEXT("/Game/06_SFX/Sound/SFX_Buy.SFX_Buy"));
	if (MyAudioAsset1.Succeeded())
	{
		buySound = MyAudioAsset1.Object;
	}
}

void UBuyButton::Clicked()
{
	UGameplayStatics::PlaySound2D(GetWorld(), buySound);
	if (!isBonus)
	{
		if (tool->upgradeIndex == 1)
		{
			tool->Buy();
			text->SetText(FText::FromString("UP"));
			if (toolIndex == 1)
			{
				TArray<AActor*> FoundTuto;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATutorisation::StaticClass(), FoundTuto);
				Tutorisation = Cast<ATutorisation>(FoundTuto[0]);

				Tutorisation->ResetPopup();
				FString textTuto = "Voila une bonne chose de faite! Retourne sur la planete et va dans ton inventaire pour equiper ton nouvel outil. C'est aussi ici que tu pourra utiliser tes boosts (enfin, quand t'en aura)";
				Tutorisation->SetPopup(textTuto, 15.0f, 4);
			}
		}
		else
		{
			tool->Upgrade();
			text->SetText(FText::FromString("UP"));
		}

		FString prix = "Prix : ";
		if (tool->currentCost[0] > 0)
		{
			prix += FString::FromInt(tool->currentCost[0]) + " fers";
		}
		if (tool->currentCost[1] > 0)
		{
			if (prix == "Prix : ")
			{
				prix += FString::FromInt(tool->currentCost[1]) + "bronzes";
			}
			else
			{
				prix += ", " + FString::FromInt(tool->currentCost[1]) + " bronzes";
			}
		}
		if (tool->currentCost[2] > 0)
		{
			if (prix == "Prix : ")
			{
				prix += FString::FromInt(tool->currentCost[2]) + " ors";
			}
			else
			{
				prix += ", " + FString::FromInt(tool->currentCost[2]) + " ors";
			}
		}
		if (tool->currentCost[3] > 0)
		{
			if (prix == "Prix : ")
			{
				prix += FString::FromInt(tool->currentCost[3]) + " diamants";
			}
			else
			{
				prix += ", " + FString::FromInt(tool->currentCost[3]) + " diamants";
			}
		}
		price->SetText(FText::FromString(prix));
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
