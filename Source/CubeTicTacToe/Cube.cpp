// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ACube::ACube()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();

	if (!CubePivot) {
		UE_LOG(LogTemp, Error, TEXT("Cube pivot should be set from blueprint!"))
		Destroy();
	}
}

// Called every frame
void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACube::SetCubePivot(UPrimitiveComponent* CubePivot) {
	this->CubePivot = CubePivot;
}


void ACube::HorizontalMovement(float Value) {
	FRotator RelativeRotation = FRotator(0, Value, 0);
	CubePivot->AddWorldRotation(RelativeRotation);
}


void ACube::VerticalMovement(float Value) {
	FRotator RelativeRotation = FRotator(Value, 0, 0);
	CubePivot->AddWorldRotation(RelativeRotation);
}


void ACube::Press() {

	FVector Location;
	FRotator Rotation;
	GetActorEyesViewPoint(Location, Rotation);

	
	APlayerController* PlayerController = (APlayerController*) GetController();
	if (PlayerController) {
		float MouseX;
		float MouseY;
		PlayerController->GetMousePosition(MouseX, MouseY);
		FVector2D MousePosition = FVector2D(MouseX, MouseY);
		FHitResult HitResult;
		if (PlayerController->GetHitResultAtScreenPosition(MousePosition, ECC_Visibility, false, HitResult)) {
			AActor* HitActor = HitResult.GetActor();
			UE_LOG(LogTemp, Warning, TEXT("Hit actor %s!"), *(HitActor->GetName()))
		}
	}

}


// Called to bind functionality to input
void ACube::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent!"))

	if (PlayerInputComponent) {
		PlayerInputComponent->BindAxis("Horizontal", this, &ACube::HorizontalMovement);
		PlayerInputComponent->BindAxis("Vertical", this, &ACube::VerticalMovement);

		PlayerInputComponent->BindAction("Click", IE_Pressed, this, &ACube::Press);
	}
}


