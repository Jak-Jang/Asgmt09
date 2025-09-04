#include "Game/J_GameModeBase.h"
#include "J_GameStateBase.h"
#include "Player/J_PlayerController.h"
#include "EngineUtils.h"

void AJ_GameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	if (AJ_GameStateBase* J_GameState = GetGameState<AJ_GameStateBase>())
	{
		J_GameState->MulticastRPCBroadcastLoginMessage(TEXT("MultiLoginTest"));
	}

	if (AJ_PlayerController* J_PlayerController = Cast<AJ_PlayerController>(NewPlayer))
	{
		AllPlayerControllers.Add(J_PlayerController);
	}
}

void AJ_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SecretNumberString = GenerateSecretNumber();
	UE_LOG(LogTemp, Warning, TEXT("Answer: %s"), *SecretNumberString);
}

void AJ_GameModeBase::PrintChatMessageString(
	AJ_PlayerController* InChattingPlayerController, const FString& InChatMessageString)
{
	FString GuessNumberString = InChatMessageString;

	if (IsGuessNumberString(GuessNumberString))
	{
		FString JudgeResultString = JudgeResult(SecretNumberString, GuessNumberString);
		for (TActorIterator<AJ_PlayerController> It(GetWorld()); It; ++It)
		{
			if (AJ_PlayerController* J_PlayerController = *It)
			{
				FString CombinedMessageString = InChatMessageString + TEXT(" -> ") + JudgeResultString;
				J_PlayerController->ClientRPCPrintChatMessageString(CombinedMessageString);
			}
		}
	}
	else
	{
		for (TActorIterator<AJ_PlayerController> It(GetWorld()); It; ++It)
		{
			if (AJ_PlayerController* J_PlayerController = *It)
			{
				J_PlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
			}
		}
	}
}

FString AJ_GameModeBase::GenerateSecretNumber()
{
	FString Result;
	TArray<int32> Numbers;

	for (int32 i = 1; i < 10; i++)
	{
		Numbers.Add(i);
	}

	for (int32 i = 0; i < 3; i++)
	{
		int32 Index = FMath::RandRange(0, Numbers.Num() - 1);
		Result += FString::FromInt(Numbers[Index]);
		Numbers.RemoveAtSwap(Index);
	}

	return Result;
}

bool AJ_GameModeBase::IsGuessNumberString(const FString& InNumberString)
{
	bool bCanPlay = false;

	do
	{
		if (InNumberString.Len() != 3) break;

		bool bIsUnique = true;
		TSet<TCHAR> UniqueDigits;

		for (TCHAR C : InNumberString)
		{
			if (FChar::IsDigit(C) == false || C == '0')
			{
				bIsUnique = false;
				break;
			}

			UniqueDigits.Add(C);
		}

		if (!bIsUnique) break;
		bCanPlay = true;
	}
	while (false);

	return bCanPlay;
}

FString AJ_GameModeBase::JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString)
{
	int32 StrikeCount = 0;
	int32 BallCount = 0;

	for (int32 i = 0; i < 3; i++)
	{
		if (InSecretNumberString[i] == InGuessNumberString[i])
		{
			StrikeCount++;
		}
		else
		{
			FString PlayerGuessChar = FString::Printf(TEXT("%c"), InGuessNumberString[i]);
			if (InSecretNumberString.Contains(PlayerGuessChar))
			{
				BallCount++;
			}
		}
	}

	if (StrikeCount == 0 && BallCount == 0) return (TEXT("Out!!!"));

	return FString::Printf(TEXT("%dS / %dB"), StrikeCount, BallCount);
}
