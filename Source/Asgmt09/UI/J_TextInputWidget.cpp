#include "UI/J_TextInputWidget.h"
#include "Player/J_PlayerController.h"
#include "Components/EditableTextBox.h"

void UJ_TextInputWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (TextInputBox->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == false)
	{
		TextInputBox->OnTextCommitted.AddDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UJ_TextInputWidget::NativeDestruct()
{
	if (TextInputBox->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == true)
	{
		TextInputBox->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}

	Super::NativeDestruct();
}

void UJ_TextInputWidget::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		if (APlayerController* OwningPlayerController = GetOwningPlayer())
		{
			if (AJ_PlayerController* OwningMyPlayerController = Cast<AJ_PlayerController>(OwningPlayerController))
			{
				OwningMyPlayerController->SetChatMessageString(Text.ToString());
				TextInputBox->SetText(FText());
			}
		}
	}
}
