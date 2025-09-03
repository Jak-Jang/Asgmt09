#include "Player/J_PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/J_TextInputWidget.h"

void AJ_PlayerController::BeginPlay()
{
	Super::BeginPlay();

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

void AJ_PlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;
	PrintChatMessageString(ChatMessageString);
}

void AJ_PlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	UKismetSystemLibrary::PrintString(this, ChatMessageString, true, true, FLinearColor::Blue, 10.0f);
}
