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
	ButtonTextState->SetText(FText::FromString("UPGRADE"));
}

void UToolsButton::UpgradeTool()
{
	tool->Upgrade();
}
