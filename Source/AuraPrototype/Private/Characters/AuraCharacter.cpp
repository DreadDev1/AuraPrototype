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
	CameraBoom->SetRelativeLocation(FVector(0.f, 0,74.f));
	CameraBoom->TargetArmLength = 250.f;
	CameraBoom->bUsePawnControlRotation = true;
	//
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
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
		if (AController* PController = GetController())
	{
			CameraBoom->TargetArmLength = 800.f;
		// Set the pitch to 65 degrees for top-down, keep yaw and roll
		FRotator NewControlRotation = Controller->GetControlRotation();
		NewControlRotation.Pitch = -75.f;
		NewControlRotation.Yaw = 0.f;   // Optional: lock to world forward
		NewControlRotation.Roll = 0.f;
			Controller->SetIgnoreLookInput(true); // Optional: disable input look
		PController->SetControlRotation(NewControlRotation);
	}
	CameraBoom->bUsePawnControlRotation = true; // Keep this enabled
}
void AAuraCharacter::DisableTopDown()
{
	bIsTopDown = false;

	if (AController* PController = GetController())
	{
		CameraBoom->TargetArmLength = 250.f;
		// Typically, allow pitch from player input
		FRotator ThirdPersonRotation = Controller->GetControlRotation();
		ThirdPersonRotation.Pitch = 0.f; // Level camera
		Controller->SetIgnoreLookInput(false); // Optional: enable input look
		PController->SetControlRotation(ThirdPersonRotation);
	}
	CameraBoom->bUsePawnControlRotation = true;
}

