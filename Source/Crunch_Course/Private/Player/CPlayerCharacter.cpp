// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACPlayerCharacter::ACPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	CameraBoom->SetupAttachment(GetRootComponent());
	ViewCam = CreateDefaultSubobject<UCameraComponent>("View Cam");
	ViewCam->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 720.f, 0.f);
}

void ACPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	APlayerController* OwningPlayerController = GetController<APlayerController>();
	if (OwningPlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = OwningPlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (InputSubsystem)
		{
			InputSubsystem->RemoveMappingContext(GameplayInputMappingContext);
			InputSubsystem->AddMappingContext(GameplayInputMappingContext, 0);
		}
	}
}

void ACPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::HandleLookInput);
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::HandleMoveInput);
	}
}

void ACPlayerCharacter::HandleLookInput(const FInputActionValue& InputActionValue)
{
	FVector2D InputVal = InputActionValue.Get<FVector2D>();
	float LookSensitivity = 0.5f;  // Tùy chỉnh theo nhu cầu
	AddControllerPitchInput(InputVal.Y * -1.0f * LookSensitivity);
	AddControllerYawInput(InputVal.X * LookSensitivity);
}

void ACPlayerCharacter::HandleMoveInput(const FInputActionValue& InputActionValue)
{
	FVector2D InputVal = InputActionValue.Get<FVector2D>();  // Lấy giá trị input (WASD/Gamepad)
	InputVal.Normalize();  // Chuẩn hóa để tốc độ ổn định

	// Kết hợp hướng trước + phải của camera để di chuyển theo góc nhìn
	AddMovementInput(GetMoveFwdDir() * InputVal.Y + GetLookRightDir() * InputVal.X);
}

FVector ACPlayerCharacter::GetLookRightDir() const
{
	return ViewCam->GetRightVector();  // Vector phải của camera (trục X)
}

FVector ACPlayerCharacter::GetLookFwdDir() const
{
	return ViewCam->GetForwardVector();  // Vector phía trước camera (trục Y)
}

FVector ACPlayerCharacter::GetMoveFwdDir() const
{
	// Loại bỏ thành phần Z để nhân vật không bay lên/rơi xuống
	return FVector::CrossProduct(GetLookRightDir(), FVector::UpVector);
}
