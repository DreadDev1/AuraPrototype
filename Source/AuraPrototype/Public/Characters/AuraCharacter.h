// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "AuraCharacter.generated.h"

UCLASS()
class AURAPROTOTYPE_API AAuraCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacter();

	void ToggleTopDown();
	
protected:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;
	FVector NewLocation = FVector(0.f, 0,74.f);
	FRotator NewRotation = FRotator(120.0f, 0.0f, 0.0f);

	// Boolean to track if top-down mode is enabled
	UPROPERTY(BlueprintReadOnly, Category = "Camera")
	bool bIsTopDown = false;
	void EnableTopDown();
	void DisableTopDown();
private:
	


	
};
