// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/UCAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UUCAnimInstance::NativeInitializeAnimation()
{
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (OwnerCharacter)
	{
		OwnerMovementComp = OwnerCharacter->GetCharacterMovement();
	}
}

void UUCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
}

void UUCAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
}
