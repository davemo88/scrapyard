// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrapyardLocalPlayer.h"
#include "Game/ScrapyardGameInstance.h"

FString UScrapyardLocalPlayer::GetNickname() const
{
	FString UserNickName = Super::GetNickname();

	bool bReplace = (UserNickName.Len() == 0);

	// Check for duplicate nicknames...and prevent reentry
	static bool bReentry = false;
	if(!bReentry)
	{
		bReentry = true;
		UScrapyardGameInstance* GameInstance = GetWorld() != NULL ? Cast<UScrapyardGameInstance>(GetWorld()->GetGameInstance()) : NULL;
		if(GameInstance)
		{
			// Check all the names that occur before ours that are the same
			const TArray<ULocalPlayer*>& LocalPlayers = GameInstance->GetLocalPlayers();
			for (int i = 0; i < LocalPlayers.Num(); ++i)
			{
				const ULocalPlayer* LocalPlayer = LocalPlayers[i];
				if( this == LocalPlayer)
				{
					break;
				}

				if( UserNickName == LocalPlayer->GetNickname())
				{
					bReplace = true;
					break;
				}
			}
		}
		bReentry = false;
	}

	if ( bReplace )
	{
		UserNickName = FString::Printf( TEXT( "Player%i" ), GetControllerId() + 1 );
	}	

	return UserNickName;
}



