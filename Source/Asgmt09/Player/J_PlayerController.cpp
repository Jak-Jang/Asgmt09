#include "Player/J_PlayerController.h"
#include "Game/J_GameModeBase.h"
#include "UI/J_TextInputWidget.h"
#include "GameFramework/GameMode.h"
#include "Kismet/GameplayStatics.h"
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
	if (AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this))
	{
		if (AJ_GameModeBase* J_GameMode = Cast<AJ_GameModeBase>(GameMode))
		{
			J_GameMode->PrintChatMessageString(this, InChatMessageString);
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
	UKismetSystemLibrary::PrintString(this, InChatMessageString, true, true, FLinearColor::Blue, 10.0f);
}
