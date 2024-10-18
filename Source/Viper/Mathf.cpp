// Fill out your copyright notice in the Description page of Project Settings.
#include "Mathf.h"
#include "Camera/CameraComponent.h"

float Mathf::Approach(float current, float target, float maxDelta)
{
    if (FMath::Abs(target - current) <= maxDelta)
    {
        return target;
    }
    return current + FMath::Sign(target - current) * maxDelta;
}

FVector Mathf::MoveTowards(const FVector& current, const FVector& target, float maxDelta)
{
    FVector direction = target - current;
    float distance = direction.Size();

    if (distance <= maxDelta || distance == 0.0f)
    {
        return target;
    }

    return current + direction.GetSafeNormal() * maxDelta;
}


FRotator Mathf::LocalInputRotation(FVector Input, const UCameraComponent* Camera)
{
    if (!Camera) return FRotator::ZeroRotator;
    FRotator TargetRotation = LocalInput(Input, Camera).Rotation();
    TargetRotation.Pitch = 0;
    TargetRotation.Roll = 0;
    return TargetRotation;

}

FVector Mathf::LocalInput(FVector Input, const UCameraComponent* Camera)
{
    if (!Camera) return Input;

    FVector CamForward = Camera->GetForwardVector();
    CamForward.Z = 0;
    CamForward *= Input.Y;

    FVector CamRight = Camera->GetRightVector();
    CamRight.Z = 0;
    CamRight *= Input.X;

    FVector Local = CamRight + CamForward;

    return Local;
}

float Mathf::Angle(const FVector& A, const FVector& B)
{
    // Normalize the vectors to ensure the calculation is accurate
    FVector NormalizedA = A.GetSafeNormal();
    FVector NormalizedB = B.GetSafeNormal();

    // Calculate the dot product and clamp it to the range [-1, 1] to avoid potential errors
    float DotProduct = FMath::Clamp(FVector::DotProduct(NormalizedA, NormalizedB), -1.0f, 1.0f);

    // Calculate the angle in radians and convert to degrees
    float AngleInRadians = FMath::Acos(DotProduct);
    return FMath::RadiansToDegrees(AngleInRadians);
}


float Mathf::SignedAngle(const FVector& A, const FVector& B, const FVector& UpVector)
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

float Mathf::OneDivided(float t)
{
    return(1/t);
}