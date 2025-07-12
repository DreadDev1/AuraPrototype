// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("PrimaryWeaponSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
