// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BasePlayerController.h"
#include "Widgets/HUD/BaseHUDWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ToolBuilderUtil.h"
#include "Characters/AuraCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interaction/Highlight/HighlightInterface.h"
#include "Kismet/GameplayStatics.h"


ABasePlayerController::ABasePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	TraceLength = 500.0;
}

void ABasePlayerController::Tick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	TraceForItem();
}

// void ABasePlayerController::CursorTrace()
// {
// 	FHitResult CursorHit;
// 	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
// 	if (!CursorHit.bBlockingHit) return;
//
// 	LastActor = ThisActor;
// 	ThisActor = CursorHit.GetActor();
//
// 	/**
// 	 * Line trace from cursor. There are several scenarios:
// 	 *  A. LastActor is null && ThisActor is null
// 	 *		- Do nothing
// 	 *	B. LastActor is null && ThisActor is valid
// 	 *		- Highlight ThisActor
// 	 *	C. LastActor is valid && ThisActor is null
// 	 *		- UnHighlight LastActor
// 	 *	D. Both actors are valid, but LastActor != ThisActor
// 	 *		- UnHighlight LastActor, and Highlight ThisActor
// 	 *	E. Both actors are valid, and are the same actor
// 	 *		- Do nothing
// 	 */
//
// 	if (LastActor == nullptr)
// 	{
// 		if (ThisActor != nullptr)
// 		{
// 			// Case B
// 			ThisActor->HighlightActor();
// 		}
// 		else
// 		{
// 			// Case A - both are null, do nothing
// 		}
// 	}
// 	else // LastActor is valid
// 	{
// 		if (ThisActor == nullptr)
// 		{
// 			// Case C
// 			LastActor->UnHighlightActor();
// 		}
// 		else // both actors are valid
// 		{
// 			if (LastActor != ThisActor)
// 			{
// 				// Case D
// 				LastActor->UnHighlightActor();
// 				ThisActor->HighlightActor();
// 			}
// 			else
// 			{
// 				// Case E - do nothing
// 			}
// 		}
// 	}
// }

void ABasePlayerController::TraceForItem()
{
	if (!IsValid(GEngine) || !IsValid(GEngine->GameViewport)) return;
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	const FVector2D ViewportCenter = ViewportSize / 2.f;
	FVector TraceStart;
	FVector Forward;
	if (!UGameplayStatics::DeprojectScreenToWorld(this, ViewportCenter, TraceStart, Forward)) return;

	const FVector TraceEnd = TraceStart + Forward * TraceLength;
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ItemTraceChannel);

	LastActor = ThisActor;
	ThisActor = HitResult.GetActor();

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Case B
			ThisActor->HighlightActor();
		}
		else
		{
			// Case A - both are null, do nothing
		}
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			// Case C
			LastActor->UnHighlightActor();
		}
		else // both actors are valid
		{
			if (LastActor != ThisActor)
			{
				// Case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// Case E - do nothing
			}
		}
	}
}

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
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABasePlayerController::Look);
	EnhancedInputComponent->BindAction(ToggleTopDownAction, ETriggerEvent::Started, this, &ABasePlayerController::ToggleTopDown);
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

void ABasePlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	AddYawInput(InputAxisVector.X);
	AddPitchInput(InputAxisVector.Y);
}

void ABasePlayerController::ToggleTopDown()
{
	AAuraCharacter* AuraCharacter = Cast<AAuraCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter()); 
	if (!AuraCharacter) return;
	AuraCharacter->ToggleTopDown();
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
