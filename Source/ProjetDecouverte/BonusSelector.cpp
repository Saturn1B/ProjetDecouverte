// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusSelector.h"
#include "MyPlayerController2.h"
#include "Materials.h"

void UBonusSelector::Clicked()
{
	TArray<AActor*> FoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPlayerController2::StaticClass(), FoundPlayers);
	AMyPlayerController2* player = Cast<AMyPlayerController2>(FoundPlayers[0]);

	if (damage) { player->damageBonus = damageBonus; }
	else { player->materialBonus = materialBonus; }
	this->SetIsEnabled(false);
}

void UBonusSelector::RestoreValue()
{
	TArray<AActor*> FoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPlayerController2::StaticClass(), FoundPlayers);
	AMyPlayerController2* player = Cast<AMyPlayerController2>(FoundPlayers[0]);

	if (damage) { player->damageBonus = 1; }
	else { player->materialBonus = 1; }
}

void UBonusSelector::Buy()
{
	TArray<AActor*> FoundMat;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMaterials::StaticClass(), FoundMat);
	materials = Cast<AMaterials>(FoundMat[0]);

	for (size_t i = 0; i < cost.Num(); i++)
	{
		materials->UpdateMaterial(i, -cost[i]);
	}
}
