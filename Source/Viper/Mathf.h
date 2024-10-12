// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"

/**
 * 
 */
class VIPER_API Mathf
{
public:
	Mathf()=delete;
	~Mathf()=delete;
	static float MoveTowards(float current, float target, float maxDelta);
	static float SignedAngle(const FVector& A, const FVector& B, const FVector& UpVector);
	static FRotator LocalInput(FVector Input, const UCameraComponent* Camera);
};
