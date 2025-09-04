#include "Player/J_PlayerState.h"
#include "Net/UnrealNetwork.h"

AJ_PlayerState::AJ_PlayerState() :
	PlayerNameString(TEXT("None")),
	CurrentGuessCount(0),
	MaxGuessCount(3)
{
	bReplicates = true;
}

void AJ_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, PlayerNameString);
	DOREPLIFETIME(ThisClass, CurrentGuessCount);
	DOREPLIFETIME(ThisClass, MaxGuessCount);
}

FString AJ_PlayerState::GetPlayerInfoString()
{
	FString PlayerInfoString = PlayerNameString + TEXT(": ") +
		FString::FromInt(CurrentGuessCount) + TEXT("/") + FString::FromInt(MaxGuessCount);
	
	return PlayerInfoString;
}
