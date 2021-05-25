// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolsUse.h"
#define LOG(fstring) GLog->Log(fstring)

void UToolsUse::UseTool()
{
	if (tool != NULL)
	{
		tool->StartMining();
		LOG(tool->GetName());
	}
}
