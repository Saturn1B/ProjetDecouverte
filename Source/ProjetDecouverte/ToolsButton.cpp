// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolsButton.h"
#define LOG(fstring) GLog->Log(fstring)

void UToolsButton::ButtonInteract()
{
	if (tool != NULL) 
	{
		if (!tool->isActive)
		{
			BuyTool();
		}
		else
		{
			UpgradeTool();
		}
	}
}

void UToolsButton::BuyTool()
{
	tool->Buy();
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AToolsShop::StaticClass(), FoundActors);
	for (UToolsActivation* activation : Cast<AToolsShop>(FoundActors[0])->toolsActivation)
	{
		if (activation->index == index)
		{
			activation->SetIsEnabled(true);
		}
	}

	ButtonTextState->SetText(FText::FromString("UPGRADE"));
}

void UToolsButton::UpgradeTool()
{
	tool->Upgrade();
}
