#include "Player/J_PlayerController.h"
#include "UI/J_TextInputWidget.h"
#include "EngineUtils.h"
#include "Kismet/KismetSystemLibrary.h"

void AJ_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() == false) return;

	SetInputMode(FInputModeUIOnly());

	if (TextInputWidgetClass)
	{
		TextInputWidgetInstance = CreateWidget<UJ_TextInputWidget>(this, TextInputWidgetClass);
		if (TextInputWidgetInstance)
		{
			TextInputWidgetInstance->AddToViewport();
		}
	}
}

void AJ_PlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void AJ_PlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	for (TActorIterator<AJ_PlayerController> It(GetWorld()); It; ++It)
	{
		if (AJ_PlayerController* PlayerController = *It)
		{
			PlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
		}
	}
}

void AJ_PlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;

	if (IsLocalController())
	{
		ServerRPCPrintChatMessageString(InChatMessageString);
	}
}

void AJ_PlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	UKismetSystemLibrary::PrintString(this, ChatMessageString, true, true, FLinearColor::Blue, 10.0f);
}
