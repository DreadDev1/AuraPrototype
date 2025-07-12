// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BaseItem.h"

#include "AuraPrototype/AuraPrototype.h"


// Sets default values
ABaseItem::ABaseItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);	
}

void ABaseItem::HighlightActor()
{
	ItemMesh->SetRenderCustomDepth(true);
	ItemMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_GREEN);
}

void ABaseItem::UnHighlightActor()
{
	ItemMesh->SetRenderCustomDepth(false);
}
