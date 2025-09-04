#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "J_GameStateBase.generated.h"

UCLASS()
class ASGMT09_API AJ_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(NetMulticast, reliable)
	void MulticastRPCBroadcastLoginMessage(const FString& InNameString = FString(TEXT("Unknown")));
};
