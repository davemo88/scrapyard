// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Online/ScrapyardGameSession.h"
#include "Online.h"
#include "GameFramework/GameSession.h"
#include "OnlineSessionSettings.h"
#include "Online/ScrapyardOnlineSettings.h"
#include "Online/ScrapyardGameSession.h"
#include "SoloDraft.h"
#include "Robots/RobotPartAssignment.h"
#include "ScrapyardGameInstance.generated.h"

class AScrapyardGameSession;

UCLASS()
class SCRAPYARD_API UScrapyardGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:

//	AScrapyardGameSession* GameSession;
	
public:	
	UScrapyardGameInstance();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URobotPartAssignment* RobotPartAssignment;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USoloDraft* SoloDraft;

//	AScrapyardGameSession* GetGameSession() const;

	virtual void Init() override;
	virtual void Shutdown() override;
	FGameInstancePIEResult StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params) override;
	virtual void StartGameInstance() override;

	 AScrapyardGameSession* GetGameSession() const;	

	
//	TSharedPtr<class FScrapyardOnlineSessionSettings> SessionSettings;
//	TSharedPtr<class FScrapyardOnlineSessionSearch> SessionSearch;

//	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
//	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
//	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
//	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
//	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

//	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
//	FDelegateHandle OnStartSessionCompleteDelegateHandle;
//	FDelegateHandle OnDestroySessionCompleteDelegateHandle;
//	FDelegateHandle OnFindSessionsCompleteDelegateHandle;
//	FDelegateHandle OnJoinSessionCompleteDelegateHandle;

//	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
//	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);
//	void OnFindSessionsComplete(bool bWasSuccessful);
//	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
//	virtual void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);	

//	/** Default number of players allowed in a game */
//	static const int32 DEFAULT_MAX_PLAYERS = 8;

//	bool HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName,  bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);
//	void FindSessions(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence);
//	bool JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);
//	bool JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, int32 SessionIndexInSearchResults);
};