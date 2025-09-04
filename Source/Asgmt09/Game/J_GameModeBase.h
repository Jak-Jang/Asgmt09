#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "J_GameModeBase.generated.h"

class AJ_PlayerController;

UCLASS()
class ASGMT09_API AJ_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	/*	TODO: 로직 구현
	 *	[V] 멀티플레이 채팅
	 *	[V] 정답 숫자 생성 로직
	 *	[V] 입력된 숫자 판단 로직
	 *	4. 게임 결과 판단 (승리, 무승부)
	 */

public:
	virtual void OnPostLogin(AController* NewPlayer) override;
	virtual void BeginPlay() override;

	void PrintChatMessageString(AJ_PlayerController* InChattingPlayerController, const FString& InChatMessageString);

	FString GenerateSecretNumber();
	bool IsGuessNumberString(const FString& InNumberString);
	FString JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString);

protected:
	FString SecretNumberString;

	TArray<TObjectPtr<AJ_PlayerController>> AllPlayerControllers;
};
