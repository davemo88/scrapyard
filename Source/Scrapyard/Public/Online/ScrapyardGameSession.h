// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Online.h"
#include "GameFramework/GameSession.h"
#include "OnlineSessionSettings.h"
#include "Online/ScrapyardOnlineSettings.h"
#include "ScrapyardGameSession.generated.h"

UCLASS()
class SCRAPYARD_API AScrapyardGameSession : public AGameSession
{
	GENERATED_BODY()
	
protected:
	TSharedPtr<class FScrapyardOnlineSessionSettings> SessionSettings;
	TSharedPtr<class FScrapyardOnlineSessionSearch> SessionSearch;

	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;

	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	virtual void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);	

public:

	AScrapyardGameSession();

	/** Default number of players allowed in a game */
	static const int32 DEFAULT_MAX_PLAYERS = 8;

	bool HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName,  bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);
	void FindSessions(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence);
	bool JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);
	bool JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, int32 SessionIndexInSearchResults);
};
