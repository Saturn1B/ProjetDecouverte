// Fill out your copyright notice in the Description page of Project Settings.


#include "BigCameraShake.h"

UBigCameraShake::UBigCameraShake()
{
	OscillationDuration = 0.7f;
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.15f;

	RotOscillation.Pitch.Amplitude = FMath::RandRange(5.0f, 10.0f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(25.0f, 35.0f);

	RotOscillation.Yaw.Amplitude = FMath::RandRange(5.0f, 10.0f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(25.0f, 35.0f);
}