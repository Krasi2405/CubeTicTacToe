// Fill out your copyright notice in the Description page of Project Settings.


#include "Square.h"
#include "TicTacToeField.h"
#include "TicTacToePlayerController.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ASquare::ASquare()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	if (bSetPlayerOwner) {
		return;
	}
	SetSquareMeshMaterial(PlayerOneMaterial);
	
	OwnerField->CheckSquare(this, PlayerIndex::FirstPlayer);
	bSetPlayerOwner = true;
	bDisabled = true;
}

void ASquare::CheckO() {
	SetSquareMeshMaterial(PlayerTwoMaterial);
	OwnerField->CheckSquare(this, PlayerIndex::SecondPlayer);
	bSetPlayerOwner = true;
	bDisabled = true;
}


void ASquare::SetOwnerField(ATicTacToeField* Field) {
	OwnerField = Field;
}


void ASquare::Disable() {
	if (!bSetPlayerOwner) {
		bDisabled = false;
	}
}

void ASquare::Enable() {
	if (!bSetPlayerOwner) {
		bDisabled = true;
	}
}

bool ASquare::IsDisabled() {
	return bDisabled;
}