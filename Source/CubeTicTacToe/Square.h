// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "Square.generated.h"

class ATicTacToeField;
enum class PlayerIndex;

UCLASS(ClassGroup=GroupName)
class CUBETICTACTOE_API ASquare : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASquare();

	void SetOwnerField(ATicTacToeField* Field);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UPrimitiveComponent* SquareMesh;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CheckX();

	void CheckO();

	UFUNCTION(BlueprintCallable)
	void SetSquareMesh(UPrimitiveComponent* SquarePrimitive);

	void Disable();

	void Enable();

	bool IsDisabled();

	PlayerIndex GetPlayerOwner();

private:
	PlayerIndex PlayerOwner;

	bool bSetPlayerOwner = false;

	bool bDisabled = false;

	ATicTacToeField* OwnerField = nullptr;

	UPROPERTY(EditAnywhere)
	UMaterial* PlayerOneMaterial;

	UPROPERTY(EditAnywhere)
	UMaterial* PlayerTwoMaterial;

	UPROPERTY(EditAnywhere)
	UMaterial* EnabledMaterial;

	UPROPERTY(EditAnywhere)
	UMaterial* DisabledMaterial;

	void SetSquareMeshMaterial(UMaterialInterface* Material);

	void Check(PlayerIndex Player, UMaterial* PlayerMaterial);
};
