// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacter.h"
#include "InputActionValue.h"
#include "CPlayerCharacter.generated.h"

/**
 *
 */
UCLASS()
class ACPlayerCharacter : public ACCharacter
{
	GENERATED_BODY()
public:
	ACPlayerCharacter();
	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	/*************************************************/
	/*                  Camera View                  */
	/*************************************************/
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	class UCameraComponent* ViewCam;

	/*************************************************/
	/*                      Input                    */
	/*************************************************/
private:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* JumpInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* GameplayInputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* LookInputAction;  // Input Action cho xoay camera

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MoveInputAction;  // Input Action cho di chuyển

	// Hàm xử lý input
	void HandleLookInput(const FInputActionValue& InputActionValue);
	void HandleMoveInput(const FInputActionValue& InputActionValue);

	// Hàm trợ giúp tính hướng di chuyển
	FVector GetLookRightDir() const;  // Lấy vector phải của camera
	FVector GetLookFwdDir() const;    // Lấy vector phía trước camera
	FVector GetMoveFwdDir() const;    // Lấy hướng di chuyển thực tế (loại bỏ thành phần Z)
};