// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraPrototype/Public/Characters/AuraCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


AAuraCharacter::AAuraCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocation(NewLocation, false);
	CameraBoom->TargetArmLength = 250.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AAuraCharacter::ToggleTopDown()
{
	if (!bIsTopDown)
	{
		EnableTopDown();
	}
	else
	{
		DisableTopDown();
	}
}

void AAuraCharacter::EnableTopDown()
{
	bIsTopDown = true;
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->SetRelativeRotation(NewRotation);
}

void AAuraCharacter::DisableTopDown()
{
	bIsTopDown = false;
	CameraBoom->TargetArmLength = 250.f;
	CameraBoom->SetRelativeRotation(FRotator(0.f,0.f,0.f));
}

