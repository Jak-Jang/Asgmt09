#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "J_PlayerState.generated.h"

UCLASS()
class ASGMT09_API AJ_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AJ_PlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FString GetPlayerInfoString();

	UPROPERTY(Replicated)
	FString PlayerNameString;
	UPROPERTY(Replicated)
	int32 CurrentGuessCount;
	UPROPERTY(Replicated)
	int32 MaxGuessCount;
};
