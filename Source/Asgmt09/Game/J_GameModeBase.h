#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "J_GameModeBase.generated.h"

class AJ_PlayerController;

UCLASS()
class ASGMT09_API AJ_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void OnPostLogin(AController* NewPlayer) override;
	virtual void BeginPlay() override;

	void PrintChatMessageString(AJ_PlayerController* InChattingPlayerController, const FString& InChatMessageString);

	FString GenerateSecretNumber();
	bool IsGuessNumberString(const FString& InNumberString);
	FString JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString);

	void IncreaseGuessCount(AJ_PlayerController* InChattingPlayerController);

	void ResetGame();
	void JudgeGame(AJ_PlayerController* InChattingPlayerController, int32 InStrikeCount);

protected:
	FString SecretNumberString;

	TArray<TObjectPtr<AJ_PlayerController>> AllPlayerControllers;
};
