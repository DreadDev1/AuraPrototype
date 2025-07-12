// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/Highlight/HighlightInterface.h"
#include "BaseItem.generated.h"

UCLASS()
class AURAPROTOTYPE_API ABaseItem : public AActor, public IHighlightInterface
{
	GENERATED_BODY()

public:

	ABaseItem();
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ItemMesh;
};
