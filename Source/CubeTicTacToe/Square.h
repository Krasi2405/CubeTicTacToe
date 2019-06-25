// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Square.generated.h"

UCLASS(ClassGroup=GroupName)
class CUBETICTACTOE_API ASquare : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASquare();

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


private:
	bool hasSetOwner = false;

	UPROPERTY(EditAnywhere)
	UMaterial* PlayerOneMaterial;

	UPROPERTY(EditAnywhere)
	UMaterial* PlayerTwoMaterial;

	void SetSquareMeshMaterial(UMaterialInterface* Material);
};
