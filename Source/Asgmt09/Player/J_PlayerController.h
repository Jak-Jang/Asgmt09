#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "J_PlayerController.generated.h"

class UJ_TextInputWidget;
class UUserWidget;

UCLASS()
class ASGMT09_API AJ_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AJ_PlayerController();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;

	UFUNCTION(Client, Reliable)
	void ClientRPCPrintChatMessageString(const FString& InChatMessageString);
	UFUNCTION(Server, Reliable)
	void ServerRPCPrintChatMessageString(const FString& InChatMessageString);

	void SetChatMessageString(const FString& InChatMessageString);
	void PrintChatMessageString(const FString& InChatMessageString);

	UPROPERTY(Replicated, BlueprintReadOnly)
	FText NoticeText;
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UJ_TextInputWidget> TextInputWidgetClass;
	UPROPERTY()
	TObjectPtr<UJ_TextInputWidget> TextInputWidgetInstance;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> NoticeTextWidgetClass;
	UPROPERTY()
	TObjectPtr<UUserWidget> NoticeTextWidgetInstance;

	FString ChatMessageString;
};
