// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class IHighlightInterface;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UBaseHUDWidget;
class AAuraCharacter;


UCLASS()
class AURAPROTOTYPE_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABasePlayerController();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
#pragma region Input Mapping Context and Actions
	UPROPERTY(EditDefaultsOnly, Category = "Aura Prototype|Inputs|Input Mapping Context")
	TArray<TObjectPtr<UInputMappingContext>> DefaultIMCs;

	void Interact();
	UPROPERTY(EditDefaultsOnly, Category = "Aura Prototype|Inputs|Input Actions")
	TObjectPtr<UInputAction> InteractAction;

	void Move(const FInputActionValue& InputActionValue);
	UPROPERTY(EditDefaultsOnly, Category="Aura Prototype|Inputs|Input Actions")
	TObjectPtr<UInputAction> MoveAction;

	void Look(const FInputActionValue& InputActionValue);
	UPROPERTY(EditDefaultsOnly, Category="Aura Prototype|Inputs|Input Actions")
	TObjectPtr<UInputAction> LookAction;

	void ToggleTopDown();
	UPROPERTY(EditDefaultsOnly, Category="Aura Prototype|Inputs|Input Actions")
	TObjectPtr<UInputAction> ToggleTopDownAction;
	
#pragma endregion

#pragma region Interface Functions and Varaivles
	//void CursorTrace();

	void TraceForItem();
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TEnumAsByte<ECollisionChannel> ItemTraceChannel;
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	double TraceLength;
	
	TScriptInterface<IHighlightInterface> LastActor;
	TScriptInterface<IHighlightInterface> ThisActor;
#pragma endregion
	
	void CreateHUDWidget();
	UPROPERTY(EditDefaultsOnly, Category = "Aura Prototype|Widgets|HUD")
	TSubclassOf<UBaseHUDWidget> HUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UBaseHUDWidget> HUDWidget;
	
};
