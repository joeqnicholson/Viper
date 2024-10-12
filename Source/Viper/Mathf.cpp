// Fill out your copyright notice in the Description page of Project Settings.
#include "Mathf.h"
#include "Camera/CameraComponent.h"

float Mathf::MoveTowards(float current, float target, float maxDelta)
{
    if (FMath::Abs(target - current) <= maxDelta)
    {
        return target;
    }
    return current + FMath::Sign(target - current) * maxDelta;
}

FRotator Mathf::LocalInput(FVector Input, const UCameraComponent* Camera)
{

    if (!Camera) return FRotator::ZeroRotator;

    FVector CamForward = Camera->GetForwardVector();
    CamForward.Z = 0;
    CamForward *= Input.Y;

    FVector CamRight = Camera->GetRightVector();
    CamRight.Z = 0;
    CamRight *= Input.X;

    FRotator TargetRotation = (CamRight + CamForward).Rotation();
    TargetRotation.Pitch = 0;
    TargetRotation.Roll = 0;

    return TargetRotation;

}

float SignedAngle(const FVector& A, const FVector& B, const FVector& UpVector)
{

    FVector NormA = A.GetSafeNormal();
    FVector NormB = B.GetSafeNormal();

    // Calculate the dot product
    float DotProd = FVector::DotProduct(NormA, NormB);

    // Get the angle
    float Angle = FMath::Acos(DotProd);

    // Use the cross product to get the angle sign
    FVector CrossProd = FVector::CrossProduct(NormA, NormB);
    if (FVector::DotProduct(CrossProd, UpVector) < 0)
    {
        Angle *= -1; // Negative angle
    }

    return FMath::RadiansToDegrees(Angle); // Angle in radians

}