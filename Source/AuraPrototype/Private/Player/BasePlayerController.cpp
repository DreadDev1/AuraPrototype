// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BasePlayerController.h"
#include "Widgets/HUD/BaseHUDWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(Subsystem))
	{
		for (UInputMappingContext* CurrentContext : DefaultIMCs) { Subsystem->AddMappingContext(CurrentContext, 0); }
	}
	CreateHUDWidget();
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ABasePlayerController::Interact);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABasePlayerController::Move);


}

void ABasePlayerController::Interact()
{
	UE_LOG(LogTemp, Log, TEXT("Primary Interact"))
}

void ABasePlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ABasePlayerController::CreateHUDWidget()
{
	if (!IsLocalController()) return;
	HUDWidget = CreateWidget<UBaseHUDWidget>(this, HUDWidgetClass);
	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport();
	}
}
