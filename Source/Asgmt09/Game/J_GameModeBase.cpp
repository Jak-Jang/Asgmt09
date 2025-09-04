#include "Game/J_GameModeBase.h"
#include "J_GameStateBase.h"

void AJ_GameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	if (AJ_GameStateBase* J_GameState = GetGameState<AJ_GameStateBase>())
	{
		J_GameState->MulticastRPCBroadcastLoginMessage(TEXT("MultiLoginTest"));
	}
}
