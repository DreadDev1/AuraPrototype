// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Interaction/Highlight/HighlightInterface.h"
#include "AuraEnemy.generated.h"

UCLASS()
class AURAPROTOTYPE_API AAuraEnemy : public ABaseCharacter, public IHighlightInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	
};
