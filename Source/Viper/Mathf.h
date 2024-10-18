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
	static float Approach(float current, float target, float maxDelta);
	static FVector MoveTowards(const FVector& current, const FVector& target, float maxDelta);
	static float SignedAngle(const FVector& A, const FVector& B, const FVector& UpVector);
	static float Angle(const FVector& A, const FVector& B);
	static FVector LocalInput(FVector Input, const UCameraComponent* Camera);
	static FRotator LocalInputRotation(FVector Input, const UCameraComponent* Camera);
	static float OneDivided(float t);
};
