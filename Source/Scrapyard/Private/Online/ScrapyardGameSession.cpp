// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrapyardGameSession.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Online/ScrapyardOnlineSettings.h"

AScrapyardGameSession::AScrapyardGameSession()
{
  UE_LOG(LogOnline, Log, TEXT("AScrapyardGameSession Constructor"));
  OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &AScrapyardGameSession::OnCreateSessionComplete);
  OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &AScrapyardGameSession::OnStartOnlineGameComplete);
  OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &AScrapyardGameSession::OnFindSessionsComplete);
  OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &AScrapyardGameSession::OnJoinSessionComplete);
  OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &AScrapyardGameSession::OnDestroySessionComplete);
}

//bool AScrapyardGameSession::HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers)
bool AScrapyardGameSession::HostSession(FUniqueNetIdRepl UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers)
{
  IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();

  if (OnlineSub)
  {
    IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

    if (Sessions.IsValid() && UserId.IsValid())
    {
      UE_LOG(LogOnline, Log, TEXT("about to try to make the session settings"));

      SessionSettings = MakeShareable(new FScrapyardOnlineSessionSettings());

      SessionSettings->Set(SETTING_MAPNAME, FString("BattleLevel"), EOnlineDataAdvertisementType::ViaOnlineService);

      OnCreateSessionCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

      return Sessions->CreateSession(*UserId, SessionName, *SessionSettings);
    }
    else
    {
      UE_LOG(LogOnline, Log, TEXT("couldn't host the session"));
    }
  }
  else
  {
    UE_LOG(LogOnline, Log, TEXT("couldn't host the session"));
  }

  return false;
}

//void AScrapyardGameSession::FindSessions(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence)
void AScrapyardGameSession::FindSessions(FUniqueNetIdRepl UserId, FName SessionName, bool bIsLAN, bool bIsPresence)
{
  IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

  if (OnlineSub)
  {
    IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

    if (Sessions.IsValid() && UserId.IsValid())
    {
      SessionSearch = MakeShareable(new FScrapyardOnlineSessionSearch(bIsLAN, bIsPresence));

      TSharedRef<FScrapyardOnlineSessionSearch> SessionSearchRef = SessionSearch.ToSharedRef();

      OnFindSessionsCompleteDelegateHandle = Sessions->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
      
      Sessions->FindSessions(*UserId, SessionSearchRef);
    }
  }
  else
  {
    // If something goes wrong, just call the Delegate Function directly with "false".
    OnFindSessionsComplete(false);
  }
}

//bool AScrapyardGameSession::JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult)
bool AScrapyardGameSession::JoinSession(FUniqueNetIdRepl UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult)
{
  // Return bool
  bool bSuccessful = false;

  IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

  if (OnlineSub)
  {
    IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

    if (Sessions.IsValid() && UserId.IsValid())
    {
      OnJoinSessionCompleteDelegateHandle = Sessions->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
      
      bSuccessful = Sessions->JoinSession(*UserId, SessionName, SearchResult);
    }
  }
  return bSuccessful;
}

//bool AScrapyardGameSession::JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, int32 SessionIndexInSearchResults)
bool AScrapyardGameSession::JoinSession(FUniqueNetIdRepl UserId, FName SessionName, int32 SessionIndexInSearchResults)
{
  const FOnlineSessionSearchResult& SearchResult = SessionSearch->SearchResults[SessionIndexInSearchResults];
  return JoinSession(UserId, SessionName, SearchResult);
}

void AScrapyardGameSession::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
  GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnCreateSessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful));

  IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
  if (OnlineSub)
  {
    IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

    if (Sessions.IsValid())
    {
      Sessions->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
      if (bWasSuccessful)
      {
        OnStartSessionCompleteDelegateHandle = Sessions->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);

        Sessions->StartSession(SessionName);
      }
    }
    
  }
}

void AScrapyardGameSession::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
  GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnStartSessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful));

  IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
  if (OnlineSub)
  {
    IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
    if (Sessions.IsValid())
    {
      Sessions->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
    }
  }

  // If the start was successful, we can open a NewMap if we want. Make sure to use "listen" as a parameter!
  if (bWasSuccessful)
  {
    UGameplayStatics::OpenLevel(GetWorld(), "/Game/Levels/BattleLevel", true, "listen");
  }
}

void AScrapyardGameSession::OnFindSessionsComplete(bool bWasSuccessful)
{
  GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OFindSessionsComplete bSuccess: %d"), bWasSuccessful));

  // Get OnlineSubsystem we want to work with
  IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
  if (OnlineSub)
  {
    // Get SessionInterface of the OnlineSubsystem
    IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
    if (Sessions.IsValid())
    {
      // Clear the Delegate handle, since we finished this call
      Sessions->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);

      // Just debugging the Number of Search results. Can be displayed in UMG or something later on
      GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Num Search Results: %d"), SessionSearch->SearchResults.Num()));
    
      // If we have found at least 1 session, we just going to debug them. You could add them to a list of UMG Widgets, like it is done in the BP version!
      if (SessionSearch->SearchResults.Num() > 0)
      {
        GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Attempting to Join")));
        ULocalPlayer* Player = GetWorld()->GetFirstLocalPlayerFromController();
        JoinSession(Player->GetPreferredUniqueNetId(), FName(TEXT("TestSession")), 0);
        // "SessionSearch->SearchResults" is an Array that contains all the information. You can access the Session in this and get a lot of information.
        // This can be customized later on with your own classes to add more information that can be set and displayed
        for (int32 SearchIdx = 0; SearchIdx < SessionSearch->SearchResults.Num(); SearchIdx++)
        {
          // OwningUserName is just the SessionName for now. I guess you can create your own Host Settings class and GameSession Class and add a proper GameServer Name here.
          // This is something you can't do in Blueprint for example!
          GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Session Number: %d | Sessionname: %s "), SearchIdx+1, *(SessionSearch->SearchResults[SearchIdx].Session.OwningUserName)));
        }
      }
    }
  }
}

void AScrapyardGameSession::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
  GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnJoinSessionComplete %s, %d"), *SessionName.ToString(), static_cast<int32>(Result)));

  IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
  if (OnlineSub)
  {
    IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

    if (Sessions.IsValid())
    {
      Sessions->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);

      // Get the first local PlayerController, so we can call "ClientTravel" to get to the Server Map
      APlayerController * const PlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());

      // We need a FString to use ClientTravel and we can let the SessionInterface contruct such a
      // String for us by giving him the SessionName and an empty String. We want to do this, because
      // Every OnlineSubsystem uses different TravelURLs
      FString TravelURL;

      if (PlayerController && Sessions->GetResolvedConnectString(SessionName, TravelURL))
      {
        // Finally call the ClienTravel. If you want, you could print the TravelURL to see
        // how it really looks like
        PlayerController->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute);
      }
    }
  }
}

void AScrapyardGameSession::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
  GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnDestroySessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful));

  IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
  if (OnlineSub)
  {
    IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

    if (Sessions.IsValid())
    {
      Sessions->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);

      if (bWasSuccessful)
      {
        UGameplayStatics::OpenLevel(GetWorld(), "/Game/Levels/DebugMainLevel", true);
      }
    }
  }
}

const TArray<FOnlineSessionSearchResult> & AScrapyardGameSession::GetSearchResults() const
{
  return SessionSearch->SearchResults;
}

void AScrapyardGameSession::RegisterServer()
{
  Super::RegisterServer();
  
  UE_LOG(LogOnline, Log, TEXT("RegisterServer. Hosting DedicatedSession"));

  IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();

  if (OnlineSub)
  {
    IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

    if (Sessions.IsValid())
    {
      UE_LOG(LogOnline, Log, TEXT("about to try to make the session settings"));

      SessionSettings = MakeShareable(new FScrapyardOnlineSessionSettings());

      SessionSettings->Set(SETTING_MAPNAME, FString("BattleLevel"), EOnlineDataAdvertisementType::ViaOnlineService);

      OnCreateSessionCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

      Sessions->CreateSession(0, FName(TEXT("DedicatedSession")), *SessionSettings);
    }
    else
    {
      UE_LOG(LogOnline, Log, TEXT("sessions interface is invalid"));
    }
  }
  else
  {
    UE_LOG(LogOnline, Log, TEXT("no online subsystem found"));
  }
}
