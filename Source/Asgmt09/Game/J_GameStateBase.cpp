#include "Game/J_GameStateBase.h"
#include "Player/J_PlayerController.h"
#include "Kismet/GameplayStatics.h"

void AJ_GameStateBase::MulticastRPCBroadcastLoginMessage_Implementation(const FString& InNameString)
{
	if (HasAuthority() == false)
	{
		if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			if (AJ_PlayerController* J_PlayerController = Cast<AJ_PlayerController>(PlayerController))
			{
				FString NoticeString = InNameString + TEXT(" has joined the game");
				J_PlayerController->PrintChatMessageString(NoticeString);
			}
		}
	}
}
