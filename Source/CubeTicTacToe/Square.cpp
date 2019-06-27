// Fill out your copyright notice in the Description page of Project Settings.


#include "Square.h"
#include "TicTacToeField.h"
#include "TicTacToePlayerController.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ASquare::ASquare()
{
	PlayerOwner = PlayerIndex::None;
}

// Called when the game starts or when spawned
void ASquare::BeginPlay()
{
	Super::BeginPlay();

	if (!SquareMesh) {
		UE_LOG(LogTemp, Error, TEXT("Mesh not set for Square"));
		Destroy();
	}
}

// Called every frame
void ASquare::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASquare::SetSquareMesh(UPrimitiveComponent* SquarePrimitive) {
	SquareMesh = SquarePrimitive;
}


void ASquare::SetSquareMeshMaterial(UMaterialInterface* Material) {
	if (Material) {
		SquareMesh->SetMaterial(0, Material);
	}
}

void ASquare::CheckX() {
	Check(PlayerIndex::FirstPlayer, PlayerOneMaterial);
}

void ASquare::CheckO() {
	Check(PlayerIndex::SecondPlayer, PlayerTwoMaterial);
}


void ASquare::Check(PlayerIndex Player, UMaterial* PlayerMaterial) {
	if (bSetPlayerOwner) {
		UE_LOG(LogTemp, Error, TEXT("Attempting to set Square owner who is already set!"))
		return;
	}
	SetSquareMeshMaterial(PlayerMaterial);
	bSetPlayerOwner = true;
	bDisabled = true;
	PlayerOwner = Player;
	OwnerField->CheckSquare(this, Player);
	
}


void ASquare::SetOwnerField(ATicTacToeField* Field) {
	OwnerField = Field;
}


void ASquare::Disable() {
	if (PlayerOwner == PlayerIndex::None) {
		bDisabled = true;
		SetSquareMeshMaterial(DisabledMaterial);
	}
}


void ASquare::Enable() {
	if (PlayerOwner == PlayerIndex::None) {
		bDisabled = false;
		SetSquareMeshMaterial(EnabledMaterial);
	}
}


bool ASquare::IsDisabled() {
	return bDisabled;
}


PlayerIndex ASquare::GetPlayerOwner() {
	return PlayerOwner;
}