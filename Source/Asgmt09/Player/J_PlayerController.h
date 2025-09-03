#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "J_PlayerController.generated.h"

class UJ_TextInputWidget;

UCLASS()
class ASGMT09_API AJ_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void SetChatMessageString(const FString& InChatMessageString);
	void PrintChatMessageString(const FString& InChatMessageString);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UJ_TextInputWidget> TextInputWidgetClass;
	UPROPERTY()
	TObjectPtr<UJ_TextInputWidget> TextInputWidgetInstance;

	FString ChatMessageString;
};
