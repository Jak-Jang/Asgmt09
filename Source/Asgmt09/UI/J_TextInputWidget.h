#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "J_TextInputWidget.generated.h"

class UEditableTextBox;

UCLASS()
class ASGMT09_API UJ_TextInputWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> TextInputBox;

protected:
	UFUNCTION()
	void OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
};
