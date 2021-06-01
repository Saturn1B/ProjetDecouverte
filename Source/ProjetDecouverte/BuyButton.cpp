// Fill out your copyright notice in the Description page of Project Settings.


#include "BuyButton.h"
#include "Shop.h"
#include "Tools.h"
#define LOG(fstring) GLog->Log(fstring)

UBuyButton::UBuyButton()
{
	OnClicked.AddDynamic(this, &UBuyButton::Clicked);
}

void UBuyButton::Clicked()
{
	//for (ATools* tool : shop->toolsArray)
	//{
		//if(tool->index == toolIndex)
		//{
			if(tool->upgradeIndex == 0)
			{
				tool->Buy();
				text->SetText(FText::FromString("UP"));
			}
			else
			{
				tool->Upgrade();
				text->SetText(FText::FromString("UP"));
			}
			//break;
		//}
	//}
}
