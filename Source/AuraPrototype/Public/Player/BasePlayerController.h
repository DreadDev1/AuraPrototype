// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ITracingInterface;
class UBaseHUDWidget;


UCLASS()
class AURAPROTOTYPE_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Aura Prototype|Inputs|Input Mapping Context")
	TArray<TObjectPtr<UInputMappingContext>> DefaultIMCs;

	void Interact();
	UPROPERTY(EditDefaultsOnly, Category = "Aura Prototype|Inputs|Input Actions")
	TObjectPtr<UInputAction> PrimaryInteractAction;

	void CreateHUDWidget();
	UPROPERTY(EditDefaultsOnly, Category = "Aura Prototype|Widgets|HUD")
	TSubclassOf<UBaseHUDWidget> HUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UBaseHUDWidget> HUDWidget;
	
};
