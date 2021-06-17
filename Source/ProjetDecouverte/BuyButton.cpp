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
		if (tool->upgradeIndex == 0)
		{
			tool->Buy();
			text->SetText(FText::FromString("UP"));
			if (toolIndex == 1)
			{
				TArray<AActor*> FoundTuto;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATutorisation::StaticClass(), FoundTuto);
				Tutorisation = Cast<ATutorisation>(FoundTuto[0]);

				Tutorisation->ResetPopup();
				FString textTuto = "Voila une bonne chose de faite! Tu pourra aussi les ameliorer quand t'aura plus de ressource. Pour l'instant retourne sur la planete et va dans ton inventaire pour equiper ton nouvel outil. C'est aussi ici que tu pourra utiliser tes boosts (enfin, quand t'en aura)";
				Tutorisation->SetPopup(textTuto, 20.0f, 4);
			}
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
