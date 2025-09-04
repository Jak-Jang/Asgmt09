#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "J_GameModeBase.generated.h"

UCLASS()
class ASGMT09_API AJ_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	/*	TODO: 로직 구현
	 *	1. 멀티플레이 채팅
	 *	2. 정답 숫자 생성 로직
	 *	3. 입력된 숫자 판단 로직
	 *	4. 게임 결과 판단 (승리, 무승부)
	 */

public:
	virtual void OnPostLogin(AController* NewPlayer) override;
};
