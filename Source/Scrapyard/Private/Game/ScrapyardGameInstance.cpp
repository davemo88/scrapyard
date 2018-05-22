// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrapyardGameInstance.h"
#include "Misc/CoreDelegates.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/OnlineSession.h"
#include "Framework/Application/SlateApplication.h"
#include "Engine/LocalPlayer.h"
#include "Engine/Engine.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"
#include "Game/ScrapyardGameViewportClient.h"
#include "Robots/RobotCharacter.h"
#include "Robots/RobotPlayerState.h"
#include "Robots/RobotPlayerController.h"
#include "UI/Menu/ScrapyardMainMenu.h"

namespace ScrapyardGameInstanceState
{
const FName None = FName(TEXT("None"));
	const FName PendingInvite = FName(TEXT("PendingInvite"));
	const FName MainMenu = FName(TEXT("MainMenu"));
	const FName MessageMenu = FName(TEXT("MessageMenu"));
	const FName Playing = FName(TEXT("Playing"));
}

UScrapyardGameInstance::UScrapyardGameInstance()
	: OnlineMode(EOnlineMode::Online)
	, bIsLicensed(true)
{
// TODO: find the right place for these
	RobotPartAssignment = CreateDefaultSubobject<URobotPartAssignment>(TEXT("RobotPartAssignment"));
	SoloDraft = CreateDefaultSubobject<USoloDraft>(TEXT("SoloDraft"));
};

bool UScrapyardGameInstance::Tick(float DeltaSeconds)
{
	// Dedicated server doesn't need to worry about game state
	if (IsRunningDedicatedServer() == true)
	{
		return true;
	}

	MaybeChangeState();

	UScrapyardGameViewportClient * ScrapyardViewport = Cast<UScrapyardGameViewportClient>(GetGameViewportClient());

	// If we have a pending invite, and we are at the welcome screen, and the session is properly shut down, accept it
	if (PendingInvite.UserId.IsValid() && PendingInvite.bPrivilegesCheckedAndAllowed && CurrentState == ScrapyardGameInstanceState::PendingInvite)
	{
		IOnlineSubsystem * OnlineSub = IOnlineSubsystem::Get();
		IOnlineSessionPtr Sessions = (OnlineSub != NULL) ? OnlineSub->GetSessionInterface() : NULL;

		if (Sessions.IsValid())
		{
			EOnlineSessionState::Type SessionState = Sessions->GetSessionState(NAME_GameSession);

			if (SessionState == EOnlineSessionState::NoSession)
			{
				ULocalPlayer * NewPlayerOwner = GetFirstGamePlayer();

				if (NewPlayerOwner != nullptr)
				{
					NewPlayerOwner->SetControllerId(PendingInvite.ControllerId);
					NewPlayerOwner->SetCachedUniqueNetId(PendingInvite.UserId);
					SetOnlineMode(EOnlineMode::Online);
					JoinSession(NewPlayerOwner, PendingInvite.InviteResult);					
				}

				PendingInvite.UserId.Reset();
			}			
		}
	}

	return true;
}

AScrapyardGameSession* UScrapyardGameInstance::GetGameSession() const
{
	UWorld* const World = GetWorld();
	if (World)
	{
		AGameModeBase* const Game = World->GetAuthGameMode();
		if (Game)
		{
			return Cast<AScrapyardGameSession>(Game->GameSession);
		}
	}

	return nullptr;
}


void UScrapyardGameInstance::Init()
{
	Super::Init();

	IgnorePairingChangeForControllerId = -1;
	CurrentConnectionStatus = EOnlineServerConnectionStatus::Connected;

	LocalPlayerOnlineStatus.InsertDefaulted(0, MAX_LOCAL_PLAYERS);
	const auto OnlineSub = IOnlineSubsystem::Get();
	check(OnlineSub);
	const auto IdentityInterface = OnlineSub->GetIdentityInterface();
	check(IdentityInterface.IsValid());

	const auto SessionInterface = OnlineSub->GetSessionInterface();
	check(SessionInterface.IsValid());
	
	for (int i = 0; i < MAX_LOCAL_PLAYERS; ++i)
	{
		IdentityInterface->AddOnLoginStatusChangedDelegate_Handle(i, FOnLoginStatusChangedDelegate::CreateUObject(this, &UScrapyardGameInstance::HandleUserLoginChanged));
	}

	FCoreDelegates::ApplicationWillDeactivateDelegate.AddUObject(this, &UScrapyardGameInstance::HandleAppWillDeactivate);

	FCoreDelegates::ApplicationWillEnterBackgroundDelegate.AddUObject(this, &UScrapyardGameInstance::HandleAppSuspend);
	FCoreDelegates::ApplicationHasEnteredForegroundDelegate.AddUObject(this, &UScrapyardGameInstance::HandleAppResume);

	FCoreDelegates::OnSafeFrameChangedEvent.AddUObject(this, &UScrapyardGameInstance::HandleSafeFrameChanged);
	FCoreDelegates::ApplicationLicenseChange.AddUObject(this, &UScrapyardGameInstance::HandleAppLicenseUpdate);

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UScrapyardGameInstance::OnPreLoadMap);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UScrapyardGameInstance::OnPostLoadMap);

	bPendingEnableSplitscreen = false;

	OnlineSub->AddOnConnectionStatusChangedDelegate_Handle( FOnConnectionStatusChangedDelegate::CreateUObject( this, &UScrapyardGameInstance::HandleNetworkConnectionStatusChanged ) );

	SessionInterface->AddOnSessionFailureDelegate_Handle( FOnSessionFailureDelegate::CreateUObject( this, &UScrapyardGameInstance::HandleSessionFailure ) );
	
	OnEndSessionCompleteDelegate = FOnEndSessionCompleteDelegate::CreateUObject(this, &UScrapyardGameInstance::OnEndSessionComplete);

	// Register delegate for ticker callback
	TickDelegate = FTickerDelegate::CreateUObject(this, &UScrapyardGameInstance::Tick);
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);


}

void UScrapyardGameInstance::Shutdown()
{
	Super::Shutdown();

	// Unregister ticker delegate
	FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
}

FGameInstancePIEResult UScrapyardGameInstance::StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params)
{
	UE_LOG(LogTemp, Warning, TEXT("StartPlayInEditorGameInstance()"));
	return Super::StartPlayInEditorGameInstance(LocalPlayer, Params);
}

void UScrapyardGameInstance::StartGameInstance()
{
	TCHAR Parm[4096] = TEXT("");

	const TCHAR* Cmd = FCommandLine::Get();

	// Catch the case where we want to override the map name on startup (used for connecting to other MP instances)
	if (FParse::Token(Cmd, Parm, ARRAY_COUNT(Parm), 0) && Parm[0] != '-')
	{

		UE_LOG(LogTemp, Warning, TEXT("INSIDE!"));
		// if we're 'overriding' with the default map anyway, don't set a bogus 'playing' state.
		if (!MainMenuMap.Contains(Parm))
		{
			FURL DefaultURL;
			DefaultURL.LoadURLConfig(TEXT("DefaultPlayer"), GGameIni);

			FURL URL(&DefaultURL, Parm, TRAVEL_Partial);

			if (URL.Valid)
			{
				UEngine* const Engine = GetEngine();

				FString Error;

				const EBrowseReturnVal::Type BrowseRet = Engine->Browse(*WorldContext, URL, Error);

				if (BrowseRet == EBrowseReturnVal::Success)
				{
					// Success, we loaded the map, go directly to playing state
					GotoState(ScrapyardGameInstanceState::Playing);
					return;
				}
				else if (BrowseRet == EBrowseReturnVal::Pending)
				{
					// Assume network connection
					LoadFrontEndMap(MainMenuMap);
					AddNetworkFailureHandlers();
					ShowLoadingScreen();
					GotoState(ScrapyardGameInstanceState::Playing);
					return;
				}
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Going to Initial State"));
	GotoInitialState();
}

// starts playing a game as the host
bool UScrapyardGameInstance::HostGame(ULocalPlayer* LocalPlayer, const FString& GameType, const FString& InTravelURL)
{
	if (GetOnlineMode() == EOnlineMode::Offline)
	{
		//
		// Offline game, just go straight to map
		//

		ShowLoadingScreen();
		GotoState(ScrapyardGameInstanceState::Playing);

		// Travel to the specified match URL
		TravelURL = InTravelURL;
		GetWorld()->ServerTravel(TravelURL);
		return true;
	}

	//
	// Online game
	//

	AScrapyardGameSession* const GameSession = GetGameSession();
	if (GameSession)
	{
		// add callback delegate for completion
		OnCreatePresenceSessionCompleteDelegateHandle = GameSession->OnCreatePresenceSessionComplete().AddUObject(this, &UScrapyardGameInstance::OnCreatePresenceSessionComplete);

		TravelURL = InTravelURL;
		bool const bIsLanMatch = InTravelURL.Contains(TEXT("?bIsLanMatch"));

		//determine the map name from the travelURL
		const FString& MapNameSubStr = "/Game/Maps/";
		const FString& ChoppedMapName = TravelURL.RightChop(MapNameSubStr.Len());
		const FString& MapName = ChoppedMapName.LeftChop(ChoppedMapName.Len() - ChoppedMapName.Find("?game"));

		if (GameSession->HostSession(LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, GameType, MapName, bIsLanMatch, true, AScrapyardGameSession::DEFAULT_NUM_PLAYERS))
		{
			// If any error occured in the above, pending state would be set
			if ( (PendingState == CurrentState) || (PendingState == ScrapyardGameInstanceState::None) )
			{
				// Go ahead and go into loading state now
				// If we fail, the delegate will handle showing the proper messaging and move to the correct state
				ShowLoadingScreen();
				GotoState(ScrapyardGameInstanceState::Playing);
				return true;
			}
		}
	}

	return false;
}

bool UScrapyardGameInstance::JoinSession(ULocalPlayer* LocalPlayer, int32 SessionIndexInSearchResults)
{
	// needs to tear anything down based on current state?

	AScrapyardGameSession* const GameSession = GetGameSession();
	if (GameSession)
	{
		AddNetworkFailureHandlers();

		OnJoinSessionCompleteDelegateHandle = GameSession->OnJoinSessionComplete().AddUObject(this, &UScrapyardGameInstance::OnJoinSessionComplete);
		if (GameSession->JoinSession(LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, SessionIndexInSearchResults))
		{
			// If any error occured in the above, pending state would be set
			if ( (PendingState == CurrentState) || (PendingState == ScrapyardGameInstanceState::None) )
			{
				// Go ahead and go into loading state now
				// If we fail, the delegate will handle showing the proper messaging and move to the correct state
				ShowLoadingScreen();
				GotoState(ScrapyardGameInstanceState::Playing);
				return true;
			}
		}
	}

	return false;
}

bool UScrapyardGameInstance::JoinSession(ULocalPlayer* LocalPlayer, const FOnlineSessionSearchResult& SearchResult)
{
	// needs to tear anything down based on current state?
	AScrapyardGameSession* const GameSession = GetGameSession();
	if (GameSession)
	{
		AddNetworkFailureHandlers();

		OnJoinSessionCompleteDelegateHandle = GameSession->OnJoinSessionComplete().AddUObject(this, &UScrapyardGameInstance::OnJoinSessionComplete);
		if (GameSession->JoinSession(LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, SearchResult))
		{
			// If any error occured in the above, pending state would be set
			if ( (PendingState == CurrentState) || (PendingState == ScrapyardGameInstanceState::None) )
			{
				// Go ahead and go into loading state now
				// If we fail, the delegate will handle showing the proper messaging and move to the correct state
				ShowLoadingScreen();
				GotoState(ScrapyardGameInstanceState::Playing);
				return true;
			}
		}
	}

	return false;
}

void UScrapyardGameInstance::TravelToSession(const FName& SessionName)
{
	// Added to handle failures when joining using quickmatch (handles issue of joining a game that just ended, i.e. during game ending timer)
	AddNetworkFailureHandlers();
	ShowLoadingScreen();
	GotoState(ScrapyardGameInstanceState::Playing);
	InternalTravelToSession(SessionName);
}

void UScrapyardGameInstance::BeginHostingQuickMatch()
{
	ShowLoadingScreen();
	GotoState(ScrapyardGameInstanceState::Playing);

	// Travel to the specified match URL
	GetWorld()->ServerTravel(TEXT("/Game/Maps/Highrise?game=TDM?listen"));	
}

bool UScrapyardGameInstance::FindSessions(ULocalPlayer* PlayerOwner, bool bIsDedicatedServer, bool bFindLAN)
{
	bool bResult = false;

	check(PlayerOwner != nullptr);
	if (PlayerOwner)
	{
		AScrapyardGameSession* const GameSession = GetGameSession();
		if (GameSession)
		{
			GameSession->OnFindSessionsComplete().RemoveAll(this);
			OnSearchSessionsCompleteDelegateHandle = GameSession->OnFindSessionsComplete().AddUObject(this, &UScrapyardGameInstance::OnSearchSessionsComplete);

			GameSession->FindSessions(PlayerOwner->GetPreferredUniqueNetId(), NAME_GameSession, bFindLAN, !bIsDedicatedServer);

			bResult = true;
		}
	}

	return bResult;
}

void UScrapyardGameInstance::GotoState(FName NewState)
{
	UE_LOG( LogOnline, Log, TEXT( "GotoState: NewState: %s" ), *NewState.ToString() );

	PendingState = NewState;
}

void UScrapyardGameInstance::ShowMessageThenGotoState( const FText& Message, const FText& OKButtonString, const FText& CancelButtonString, const FName& NewState, const bool OverrideExisting, TWeakObjectPtr< ULocalPlayer > PlayerOwner )
{
	UE_LOG( LogOnline, Log, TEXT( "ShowMessageThenGotoState: Message: %s, NewState: %s" ), *Message.ToString(), *NewState.ToString() );

	const bool bAlreadyAtMessageMenu = PendingState == ScrapyardGameInstanceState::MessageMenu || CurrentState == ScrapyardGameInstanceState::MessageMenu;
	const bool bAlreadyAtDestState = PendingState == NewState || CurrentState == NewState;

	// If we are already going to the message menu, don't override unless asked to
	if ( bAlreadyAtMessageMenu && PendingMessage.NextState == NewState && !OverrideExisting )
	{
		UE_LOG( LogOnline, Log, TEXT( "ShowMessageThenGotoState: Ignoring due to higher message priority in queue (check 1)." ) );
		return;
	}

	// If we are already at the dest state, don't override unless asked
	if ( bAlreadyAtDestState && !OverrideExisting )
	{
		UE_LOG( LogOnline, Log, TEXT( "ShowMessageThenGotoState: Ignoring due to higher message priority in queue (check 3)" ) );
		return;
	}

	PendingMessage.DisplayString		= Message;
	PendingMessage.OKButtonString		= OKButtonString;
	PendingMessage.CancelButtonString	= CancelButtonString;
	PendingMessage.NextState			= NewState;
	PendingMessage.PlayerOwner			= PlayerOwner;

	if ( CurrentState == ScrapyardGameInstanceState::MessageMenu )
	{
		UE_LOG( LogOnline, Log, TEXT( "ShowMessageThenGotoState: Forcing new message" ) );
		EndMessageMenuState();
		BeginMessageMenuState();
	}
	else
	{
		GotoState(ScrapyardGameInstanceState::MessageMenu);
	}
}

void UScrapyardGameInstance::ShowMessageThenGoMain(const FText& Message, const FText& OKButtonString, const FText& CancelButtonString)
{
	ShowMessageThenGotoState(Message, OKButtonString, CancelButtonString, ScrapyardGameInstanceState::MainMenu);
}

FName UScrapyardGameInstance::GetInitialState()
{
	return ScrapyardGameInstanceState::MainMenu;
}


void UScrapyardGameInstance::GotoInitialState()
{
	GotoState(GetInitialState());
}

void UScrapyardGameInstance::RemoveExistingLocalPlayer(ULocalPlayer* ExistingPlayer)
{
	check(ExistingPlayer);
	if (ExistingPlayer->PlayerController != NULL)
	{
		// Kill the player
		ARobotCharacter* MyPawn = Cast<ARobotCharacter>(ExistingPlayer->PlayerController->GetPawn());
		if ( MyPawn )
		{
// TODO: implement
//			MyPawn->KilledBy(NULL);
		}
	}

	RemoveLocalPlayer( ExistingPlayer );
}

TSharedPtr< const FUniqueNetId > UScrapyardGameInstance::GetUniqueNetIdFromControllerId( const int ControllerId )
{
	IOnlineIdentityPtr OnlineIdentityInt = Online::GetIdentityInterface();

	if ( OnlineIdentityInt.IsValid() )
	{
		TSharedPtr<const FUniqueNetId> UniqueId = OnlineIdentityInt->GetUniquePlayerId( ControllerId );

		if ( UniqueId.IsValid() )
		{
			return UniqueId;
		}
	}

	return nullptr;
}

void UScrapyardGameInstance::SetOnlineMode(EOnlineMode InOnlineMode)
{
	OnlineMode = InOnlineMode;
	UpdateUsingMultiplayerFeatures(InOnlineMode == EOnlineMode::Online);
}


void UScrapyardGameInstance::UpdateUsingMultiplayerFeatures(bool bIsUsingMultiplayerFeatures)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub)
	{
		for (int32 i = 0; i < LocalPlayers.Num(); ++i)
		{
			ULocalPlayer* LocalPlayer = LocalPlayers[i];

			TSharedPtr<const FUniqueNetId> PlayerId = LocalPlayer->GetPreferredUniqueNetId();
			if (PlayerId.IsValid())
			{
				OnlineSub->SetUsingMultiplayerFeatures(*PlayerId, bIsUsingMultiplayerFeatures);
			}
		}
	}
}

void UScrapyardGameInstance::SetIgnorePairingChangeForControllerId( const int32 ControllerId )
{
	IgnorePairingChangeForControllerId = ControllerId;
}

bool UScrapyardGameInstance::IsLocalPlayerOnline(ULocalPlayer* LocalPlayer)
{
	if (LocalPlayer == NULL)
	{
		return false;
	}
	const auto OnlineSub = IOnlineSubsystem::Get();
	if(OnlineSub)
	{
		const auto IdentityInterface = OnlineSub->GetIdentityInterface();
		if(IdentityInterface.IsValid())
		{
			auto UniqueId = LocalPlayer->GetCachedUniqueNetId();
			if (UniqueId.IsValid())
			{
				const auto LoginStatus = IdentityInterface->GetLoginStatus(*UniqueId);
				if(LoginStatus == ELoginStatus::LoggedIn)
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool UScrapyardGameInstance::IsLocalPlayerSignedIn(ULocalPlayer* LocalPlayer)
{
	if (LocalPlayer == NULL)
	{
		return false;
	}

	const auto OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		const auto IdentityInterface = OnlineSub->GetIdentityInterface();
		if (IdentityInterface.IsValid())
		{
			auto UniqueId = LocalPlayer->GetCachedUniqueNetId();
			if (UniqueId.IsValid())
			{
				return true;
			}
		}
	}

	return false;
}

bool UScrapyardGameInstance::ValidatePlayerForOnlinePlay(ULocalPlayer* LocalPlayer)
{
	return true;
}

bool UScrapyardGameInstance::ValidatePlayerIsSignedIn(ULocalPlayer* LocalPlayer)
{
	return true;
}

void UScrapyardGameInstance::CleanupSessionOnReturnToMenu()
{
	bool bPendingOnlineOp = false;

	// end online game and then destroy it
	IOnlineSubsystem * OnlineSub = IOnlineSubsystem::Get();
	IOnlineSessionPtr Sessions = ( OnlineSub != NULL ) ? OnlineSub->GetSessionInterface() : NULL;

	if ( Sessions.IsValid() )
	{
		FName GameSession(NAME_GameSession);
		EOnlineSessionState::Type SessionState = Sessions->GetSessionState(NAME_GameSession);
		UE_LOG(LogOnline, Log, TEXT("Session %s is '%s'"), *GameSession.ToString(), EOnlineSessionState::ToString(SessionState));

		if ( EOnlineSessionState::InProgress == SessionState )
		{
			UE_LOG(LogOnline, Log, TEXT("Ending session %s on return to main menu"), *GameSession.ToString() );
			OnEndSessionCompleteDelegateHandle = Sessions->AddOnEndSessionCompleteDelegate_Handle(OnEndSessionCompleteDelegate);
			Sessions->EndSession(NAME_GameSession);
			bPendingOnlineOp = true;
		}
		else if ( EOnlineSessionState::Ending == SessionState )
		{
			UE_LOG(LogOnline, Log, TEXT("Waiting for session %s to end on return to main menu"), *GameSession.ToString() );
			OnEndSessionCompleteDelegateHandle = Sessions->AddOnEndSessionCompleteDelegate_Handle(OnEndSessionCompleteDelegate);
			bPendingOnlineOp = true;
		}
		else if ( EOnlineSessionState::Ended == SessionState || EOnlineSessionState::Pending == SessionState )
		{
			UE_LOG(LogOnline, Log, TEXT("Destroying session %s on return to main menu"), *GameSession.ToString() );
			OnDestroySessionCompleteDelegateHandle = Sessions->AddOnDestroySessionCompleteDelegate_Handle(OnEndSessionCompleteDelegate);
			Sessions->DestroySession(NAME_GameSession);
			bPendingOnlineOp = true;
		}
		else if ( EOnlineSessionState::Starting == SessionState )
		{
			UE_LOG(LogOnline, Log, TEXT("Waiting for session %s to start, and then we will end it to return to main menu"), *GameSession.ToString() );
			OnStartSessionCompleteDelegateHandle = Sessions->AddOnStartSessionCompleteDelegate_Handle(OnEndSessionCompleteDelegate);
			bPendingOnlineOp = true;
		}
	}

	if ( !bPendingOnlineOp )
	{
		//GEngine->HandleDisconnect( GetWorld(), GetWorld()->GetNetDriver() );
	}
}

void UScrapyardGameInstance::LabelPlayerAsQuitter(ULocalPlayer* LocalPlayer) const
{
	ARobotPlayerState* const PlayerState = LocalPlayer && LocalPlayer->PlayerController ? Cast<ARobotPlayerState>(LocalPlayer->PlayerController->PlayerState) : nullptr;	
	if(PlayerState)
	{
// TODO: what is this
//		PlayerState->SetQuitter(true);
	}
}

void UScrapyardGameInstance::StartOnlinePrivilegeTask(const IOnlineIdentity::FOnGetUserPrivilegeCompleteDelegate& Delegate, EUserPrivileges::Type Privilege, TSharedPtr< const FUniqueNetId > UserId)
{
//	WaitMessageWidget = SNew(SScrapyardWaitDialog)
//		.MessageText(NSLOCTEXT("NetworkStatus", "CheckingPrivilegesWithServer", "Checking privileges with server.  Please wait..."));

	if (GEngine && GEngine->GameViewport)
	{
//		UGameViewportClient* const GVC = GEngine->GameViewport;
//		GVC->AddViewportWidgetContent(WaitMessageWidget.ToSharedRef());
	}

	auto Identity = Online::GetIdentityInterface();
	if (Identity.IsValid() && UserId.IsValid())
	{		
		Identity->GetUserPrivilege(*UserId, Privilege, Delegate);
	}
	else
	{
		// Can only get away with faking the UniqueNetId here because the delegates don't use it
		Delegate.ExecuteIfBound(FUniqueNetIdString(), Privilege, (uint32)IOnlineIdentity::EPrivilegeResults::NoFailures);
	}
}

void UScrapyardGameInstance::CleanupOnlinePrivilegeTask()
{
//	if (GEngine && GEngine->GameViewport && WaitMessageWidget.IsValid())
//	{
//		UGameViewportClient* const GVC = GEngine->GameViewport;
//		GVC->RemoveViewportWidgetContent(WaitMessageWidget.ToSharedRef());
//	}
}

void UScrapyardGameInstance::DisplayOnlinePrivilegeFailureDialogs(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, uint32 PrivilegeResults)
{	
//	// Show warning that the user cannot play due to age restrictions
//	UScrapyardGameViewportClient * ScrapyardViewport = Cast<UScrapyardGameViewportClient>(GetGameViewportClient());
//	TWeakObjectPtr<ULocalPlayer> OwningPlayer;
//	if (GEngine)
//	{
//		for (auto It = GEngine->GetLocalPlayerIterator(GetWorld()); It; ++It)
//		{
//			TSharedPtr<const FUniqueNetId> OtherId = (*It)->GetPreferredUniqueNetId();
//			if (OtherId.IsValid())
//			{
//				if (UserId == (*OtherId))
//				{
//					OwningPlayer = *It;
//				}
//			}
//		}
//	}
//	
//	if (ScrapyardViewport != NULL && OwningPlayer.IsValid())
//	{
//		if ((PrivilegeResults & (uint32)IOnlineIdentity::EPrivilegeResults::AccountTypeFailure) != 0)
//		{
//			IOnlineExternalUIPtr ExternalUI = Online::GetExternalUIInterface();
//			if (ExternalUI.IsValid())
//			{
//				ExternalUI->ShowAccountUpgradeUI(UserId);
//			}
//		}
//		else if ((PrivilegeResults & (uint32)IOnlineIdentity::EPrivilegeResults::RequiredSystemUpdate) != 0)
//		{
//			ScrapyardViewport->ShowDialog(
//				OwningPlayer.Get(),
//				EScrapyardDialogType::Generic,
//				NSLOCTEXT("OnlinePrivilegeResult", "RequiredSystemUpdate", "A required system update is available.  Please upgrade to access online features."),
//				NSLOCTEXT("DialogButtons", "OKAY", "OK"),
//				FText::GetEmpty(),
//				FOnClicked::CreateUObject(this, &UScrapyardGameInstance::OnConfirmGeneric),
//				FOnClicked::CreateUObject(this, &UScrapyardGameInstance::OnConfirmGeneric)
//				);
//		}
//		else if ((PrivilegeResults & (uint32)IOnlineIdentity::EPrivilegeResults::RequiredPatchAvailable) != 0)
//		{
//			ScrapyardViewport->ShowDialog(
//				OwningPlayer.Get(),
//				EScrapyardDialogType::Generic,
//				NSLOCTEXT("OnlinePrivilegeResult", "RequiredPatchAvailable", "A required game patch is available.  Please upgrade to access online features."),
//				NSLOCTEXT("DialogButtons", "OKAY", "OK"),
//				FText::GetEmpty(),
//				FOnClicked::CreateUObject(this, &UScrapyardGameInstance::OnConfirmGeneric),
//				FOnClicked::CreateUObject(this, &UScrapyardGameInstance::OnConfirmGeneric)
//				);
//		}
//		else if ((PrivilegeResults & (uint32)IOnlineIdentity::EPrivilegeResults::AgeRestrictionFailure) != 0)
//		{
//			ScrapyardViewport->ShowDialog(
//				OwningPlayer.Get(),
//				EScrapyardDialogType::Generic,
//				NSLOCTEXT("OnlinePrivilegeResult", "AgeRestrictionFailure", "Cannot play due to age restrictions!"),
//				NSLOCTEXT("DialogButtons", "OKAY", "OK"),
//				FText::GetEmpty(),
//				FOnClicked::CreateUObject(this, &UScrapyardGameInstance::OnConfirmGeneric),
//				FOnClicked::CreateUObject(this, &UScrapyardGameInstance::OnConfirmGeneric)
//				);
//		}
//		else if ((PrivilegeResults & (uint32)IOnlineIdentity::EPrivilegeResults::UserNotFound) != 0)
//		{
//			ScrapyardViewport->ShowDialog(
//				OwningPlayer.Get(),
//				EScrapyardDialogType::Generic,
//				NSLOCTEXT("OnlinePrivilegeResult", "UserNotFound", "Cannot play due invalid user!"),
//				NSLOCTEXT("DialogButtons", "OKAY", "OK"),
//				FText::GetEmpty(),
//				FOnClicked::CreateUObject(this, &UScrapyardGameInstance::OnConfirmGeneric),
//				FOnClicked::CreateUObject(this, &UScrapyardGameInstance::OnConfirmGeneric)
//				);
//		}
//		else if ((PrivilegeResults & (uint32)IOnlineIdentity::EPrivilegeResults::GenericFailure) != 0)
//		{
//			ScrapyardViewport->ShowDialog(
//				OwningPlayer.Get(),
//				EScrapyardDialogType::Generic,
//				NSLOCTEXT("OnlinePrivilegeResult", "GenericFailure", "Cannot play online.  Check your network connection."),
//				NSLOCTEXT("DialogButtons", "OKAY", "OK"),
//				FText::GetEmpty(),
//				FOnClicked::CreateUObject(this, &UScrapyardGameInstance::OnConfirmGeneric),
//				FOnClicked::CreateUObject(this, &UScrapyardGameInstance::OnConfirmGeneric)
//				);
//		}
//	}
}

TSubclassOf<UOnlineSession> UScrapyardGameInstance::GetOnlineSessionClass()
{
// TODO: implement
//	return UScrapyardOnlineSessionClient::StaticClass();
	return UOnlineSession::StaticClass();
}

void UScrapyardGameInstance::HandleNetworkConnectionStatusChanged(  EOnlineServerConnectionStatus::Type LastConnectionStatus, EOnlineServerConnectionStatus::Type ConnectionStatus )
{
	UE_LOG( LogOnlineGame, Warning, TEXT( "UScrapyardGameInstance::HandleNetworkConnectionStatusChanged: %s" ), EOnlineServerConnectionStatus::ToString( ConnectionStatus ) );

	CurrentConnectionStatus = ConnectionStatus;
}

void UScrapyardGameInstance::HandleSessionFailure( const FUniqueNetId& NetId, ESessionFailure::Type FailureType )
{
	UE_LOG( LogOnlineGame, Warning, TEXT( "UScrapyardGameInstance::HandleSessionFailure: %u" ), (uint32)FailureType );

}

void UScrapyardGameInstance::OnPreLoadMap(const FString& MapName)
{
	if ( bPendingEnableSplitscreen )
	{
		// Allow splitscreen
		GetGameViewportClient()->SetDisableSplitscreenOverride( false );

		bPendingEnableSplitscreen = false;
	}
}

void UScrapyardGameInstance::OnPostLoadMap(UWorld*)
{
// TODO: implement viewport
	// Make sure we hide the loading screen when the level is done loading
//	UScrapyardGameViewportClient * ScrapyardViewport = Cast<UScrapyardGameViewportClient>(GetGameViewportClient());

//	if ( ScrapyardViewport != NULL )
//	{
//		ScrapyardViewport->HideLoadingScreen();
//	}
}

void UScrapyardGameInstance::OnUserCanPlayInvite(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, uint32 PrivilegeResults)
{
	CleanupOnlinePrivilegeTask();

	if (PrivilegeResults == (uint32)IOnlineIdentity::EPrivilegeResults::NoFailures)	
	{
		if (UserId == *PendingInvite.UserId)
		{
			PendingInvite.bPrivilegesCheckedAndAllowed = true;
		}		
	}
	else
	{
		DisplayOnlinePrivilegeFailureDialogs(UserId, Privilege, PrivilegeResults);
		GotoState(ScrapyardGameInstanceState::MainMenu);
	}
}

void UScrapyardGameInstance::OnEndSessionComplete( FName SessionName, bool bWasSuccessful )
{
	UE_LOG(LogOnline, Log, TEXT("UScrapyardGameInstance::OnEndSessionComplete: Session=%s bWasSuccessful=%s"), *SessionName.ToString(), bWasSuccessful ? TEXT("true") : TEXT("false") );

	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->ClearOnStartSessionCompleteDelegate_Handle  (OnStartSessionCompleteDelegateHandle);
			Sessions->ClearOnEndSessionCompleteDelegate_Handle    (OnEndSessionCompleteDelegateHandle);
			Sessions->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);
		}
	}

	// continue
	CleanupSessionOnReturnToMenu();
}

void UScrapyardGameInstance::MaybeChangeState()
{
	if ( (PendingState != CurrentState) && (PendingState != ScrapyardGameInstanceState::None) )
	{
		FName const OldState = CurrentState;

		// end current state
		EndCurrentState(PendingState);

		// begin new state
		BeginNewState(PendingState, OldState);

		// clear pending change
		PendingState = ScrapyardGameInstanceState::None;
	}
}

void UScrapyardGameInstance::EndCurrentState(FName NextState)
{
	// per-state custom ending code here
	if (CurrentState == ScrapyardGameInstanceState::PendingInvite)
	{
		EndPendingInviteState();
	}
	else if (CurrentState == ScrapyardGameInstanceState::MainMenu)
	{
		EndMainMenuState();
	}
	else if (CurrentState == ScrapyardGameInstanceState::MessageMenu)
	{
		EndMessageMenuState();
	}
	else if (CurrentState == ScrapyardGameInstanceState::Playing)
	{
		EndPlayingState();
	}

	CurrentState = ScrapyardGameInstanceState::None;
}

void UScrapyardGameInstance::BeginNewState(FName NewState, FName PrevState)
{
	// per-state custom starting code here

	if (NewState == ScrapyardGameInstanceState::PendingInvite)
	{
		BeginPendingInviteState();
	}
	else if (NewState == ScrapyardGameInstanceState::MainMenu)
	{
		BeginMainMenuState();
	}
	else if (NewState == ScrapyardGameInstanceState::MessageMenu)
	{
		BeginMessageMenuState();
	}
	else if (NewState == ScrapyardGameInstanceState::Playing)
	{
		BeginPlayingState();
	}

	CurrentState = NewState;
}

void UScrapyardGameInstance::BeginPendingInviteState()
{	
	if (LoadFrontEndMap(MainMenuMap))
	{				
		StartOnlinePrivilegeTask(IOnlineIdentity::FOnGetUserPrivilegeCompleteDelegate::CreateUObject(this, &UScrapyardGameInstance::OnUserCanPlayInvite), EUserPrivileges::CanPlayOnline, PendingInvite.UserId);
	}
	else
	{
		GotoState(ScrapyardGameInstanceState::MainMenu);
	}
}

void UScrapyardGameInstance::EndPendingInviteState()
{
	// cleanup in case the state changed before the pending invite was handled.
	CleanupOnlinePrivilegeTask();
}

void UScrapyardGameInstance::BeginMainMenuState()
{
	// Make sure we're not showing the loadscreen
	UScrapyardGameViewportClient * ScrapyardViewport = Cast<UScrapyardGameViewportClient>(GetGameViewportClient());

	if ( ScrapyardViewport != NULL )
	{
		ScrapyardViewport->HideLoadingScreen();
	}

	SetOnlineMode(EOnlineMode::Offline);

	// Set presence to menu state for the owning player
	SetPresenceForLocalPlayers(FString(TEXT("In Menu")), FVariantData(FString(TEXT("OnMenu"))));

	// load startup map
	LoadFrontEndMap(MainMenuMap);

	// player 0 gets to own the UI
	ULocalPlayer* const Player = GetFirstGamePlayer();

	MainMenuUI = MakeShareable(new FScrapyardMainMenu());
	MainMenuUI->Construct(this, Player);
	MainMenuUI->AddMenuToGameViewport();

	RemoveNetworkFailureHandlers();
}

void UScrapyardGameInstance::EndMainMenuState()
{
// TODO: menus
//	if (MainMenuUI.IsValid())
//	{
//		MainMenuUI->RemoveMenuFromGameViewport();
//		MainMenuUI = nullptr;
//	}
}

void UScrapyardGameInstance::BeginMessageMenuState()
{
	if (PendingMessage.DisplayString.IsEmpty())
	{
		UE_LOG(LogOnlineGame, Warning, TEXT("UScrapyardGameInstance::BeginMessageMenuState: Display string is empty"));
		GotoInitialState();
		return;
	}

//	// Make sure we're not showing the loadscreen
//	UScrapyardGameViewportClient * ScrapyardViewport = Cast<UScrapyardGameViewportClient>(GetGameViewportClient());

//	if ( ScrapyardViewport != NULL )
//	{
//		ScrapyardViewport->HideLoadingScreen();
//	}

//	check(!MessageMenuUI.IsValid());
//	MessageMenuUI = MakeShareable(new FScrapyardMessageMenu);
//	MessageMenuUI->Construct(this, PendingMessage.PlayerOwner, PendingMessage.DisplayString, PendingMessage.OKButtonString, PendingMessage.CancelButtonString, PendingMessage.NextState);

	PendingMessage.DisplayString = FText::GetEmpty();
}

void UScrapyardGameInstance::EndMessageMenuState()
{
//	if (MessageMenuUI.IsValid())
//	{
//		MessageMenuUI->RemoveFromGameViewport();
//		MessageMenuUI = nullptr;
//	}
}

void UScrapyardGameInstance::BeginPlayingState()
{
	bPendingEnableSplitscreen = true;

	// Set presence for playing in a map
	SetPresenceForLocalPlayers(FString(TEXT("In Game")), FVariantData(FString(TEXT("InGame"))));

	// Make sure viewport has focus
	FSlateApplication::Get().SetAllUserFocusToGameViewport();
}

void UScrapyardGameInstance::EndPlayingState()
{
	// Disallow splitscreen
	GetGameViewportClient()->SetDisableSplitscreenOverride( true );

	// Clear the players' presence information
	SetPresenceForLocalPlayers(FString(TEXT("In Menu")), FVariantData(FString(TEXT("OnMenu"))));

	UWorld* const World = GetWorld();
//	ABattleGameState* const GameState = World != NULL ? World->GetGameState<ABattleGameState>() : NULL;

//	if (GameState)
//	{
//		// Send round end events for local players
//		for (int i = 0; i < LocalPlayers.Num(); ++i)
//		{
//			auto ScrapyardPC = Cast<ARobotPlayerController>(LocalPlayers[i]->PlayerController);
//			if (ScrapyardPC)
//			{
//				// Assuming you can't win if you quit early
//	//			ScrapyardPC->ClientSendRoundEndEvent(false, GameState->ElapsedTime);
//			}
//		}

//		// Give the game state a chance to cleanup first
////		GameState->RequestFinishAndExitToMainMenu();
//	}
//	else
//	{
//		// If there is no game state, make sure the session is in a good state
//		CleanupSessionOnReturnToMenu();
//	}
	CleanupSessionOnReturnToMenu();
}

void UScrapyardGameInstance::ShowLoadingScreen()
{
// TODO: implement
	// This can be confusing, so here is what is happening:
	//	For LoadMap, we use the IScrapyardGameLoadingScreenModule interface to show the load screen
	//  This is necessary since this is a blocking call, and our viewport loading screen won't get updated.
	//  We can't use IScrapyardGameLoadingScreenModule for seamless travel though
	//  In this case, we just add a widget to the viewport, and have it update on the main thread
	//  To simplify things, we just do both, and you can't tell, one will cover the other if they both show at the same time
//	IScrapyardGameLoadingScreenModule* const LoadingScreenModule = FModuleManager::LoadModulePtr<IScrapyardGameLoadingScreenModule>("ScrapyardGameLoadingScreen");
//	if (LoadingScreenModule != nullptr)
//	{
//		LoadingScreenModule->StartInGameLoadingScreen();
//	}

//	UScrapyardGameViewportClient * ScrapyardViewport = Cast<UScrapyardGameViewportClient>(GetGameViewportClient());

//	if ( ShooterViewport != NULL )
//	{
//		ShooterViewport->ShowLoadingScreen();
//	}
}

void UScrapyardGameInstance::AddNetworkFailureHandlers()
{
	// Add network/travel error handlers (if they are not already there)
	if (GEngine->OnTravelFailure().IsBoundToObject(this) == false)
	{
		TravelLocalSessionFailureDelegateHandle = GEngine->OnTravelFailure().AddUObject(this, &UScrapyardGameInstance::TravelLocalSessionFailure);
	}
}

void UScrapyardGameInstance::RemoveNetworkFailureHandlers()
{
	// Remove the local session/travel failure bindings if they exist
	if (GEngine->OnTravelFailure().IsBoundToObject(this) == true)
	{
		GEngine->OnTravelFailure().Remove(TravelLocalSessionFailureDelegateHandle);
	}
}

void UScrapyardGameInstance::TravelLocalSessionFailure(UWorld *World, ETravelFailure::Type FailureType, const FString& ReasonString)
{
// TODO: implement menu player controller
//	AScrapyardPlayerController_Menu* const FirstPC = Cast<AScrapyardPlayerController_Menu>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
//	if (FirstPC != nullptr)
//	{
//		FText ReturnReason = NSLOCTEXT("NetworkErrors", "JoinSessionFailed", "Join Session failed.");
//		if (ReasonString.IsEmpty() == false)
//		{
//			ReturnReason = FText::Format(NSLOCTEXT("NetworkErrors", "JoinSessionFailedReasonFmt", "Join Session failed. {0}"), FText::FromString(ReasonString));
//		}

//		FText OKButton = NSLOCTEXT("DialogButtons", "OKAY", "OK");
//		ShowMessageThenGoMain(ReturnReason, OKButton, FText::GetEmpty());
//	}
}

/** Callback which is intended to be called upon finding sessions */
void UScrapyardGameInstance::OnJoinSessionComplete(EOnJoinSessionCompleteResult::Type Result)
{
	// unhook the delegate
	AScrapyardGameSession* const GameSession = GetGameSession();
	if (GameSession)
	{
		GameSession->OnJoinSessionComplete().Remove(OnJoinSessionCompleteDelegateHandle);
	}

	// Add the splitscreen player if one exists
	if (Result == EOnJoinSessionCompleteResult::Success && LocalPlayers.Num() > 1)
	{
		auto Sessions = Online::GetSessionInterface();
		if (Sessions.IsValid() && LocalPlayers[1]->GetPreferredUniqueNetId().IsValid())
		{
			Sessions->RegisterLocalPlayer(*LocalPlayers[1]->GetPreferredUniqueNetId(), NAME_GameSession,
				FOnRegisterLocalPlayerCompleteDelegate::CreateUObject(this, &UScrapyardGameInstance::OnRegisterJoiningLocalPlayerComplete));
		}
	}
	else
	{
		// We either failed or there is only a single local user
		FinishJoinSession(Result);
	}
}

void UScrapyardGameInstance::FinishJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		FText ReturnReason;
		switch (Result)
		{
		case EOnJoinSessionCompleteResult::SessionIsFull:
			ReturnReason = NSLOCTEXT("NetworkErrors", "JoinSessionFailed", "Game is full.");
			break;
		case EOnJoinSessionCompleteResult::SessionDoesNotExist:
			ReturnReason = NSLOCTEXT("NetworkErrors", "JoinSessionFailed", "Game no longer exists.");
			break;
		default:
			ReturnReason = NSLOCTEXT("NetworkErrors", "JoinSessionFailed", "Join failed.");
			break;
		}

		FText OKButton = NSLOCTEXT("DialogButtons", "OKAY", "OK");
		RemoveNetworkFailureHandlers();
		ShowMessageThenGoMain(ReturnReason, OKButton, FText::GetEmpty());
		return;
	}

	InternalTravelToSession(NAME_GameSession);
}

void UScrapyardGameInstance::OnRegisterJoiningLocalPlayerComplete(const FUniqueNetId& PlayerId, EOnJoinSessionCompleteResult::Type Result)
{
	FinishJoinSession(Result);
}

/** Callback which is intended to be called upon session creation */
void UScrapyardGameInstance::OnCreatePresenceSessionComplete(FName SessionName, bool bWasSuccessful)
{
	AScrapyardGameSession* const GameSession = GetGameSession();
	if (GameSession)
	{
		GameSession->OnCreatePresenceSessionComplete().Remove(OnCreatePresenceSessionCompleteDelegateHandle);

		// Add the splitscreen player if one exists
		if (bWasSuccessful && LocalPlayers.Num() > 1)
		{
			auto Sessions = Online::GetSessionInterface();
			if (Sessions.IsValid() && LocalPlayers[1]->GetPreferredUniqueNetId().IsValid())
			{
				Sessions->RegisterLocalPlayer(*LocalPlayers[1]->GetPreferredUniqueNetId(), NAME_GameSession,
					FOnRegisterLocalPlayerCompleteDelegate::CreateUObject(this, &UScrapyardGameInstance::OnRegisterLocalPlayerComplete));
			}
		}
		else
		{
			// We either failed or there is only a single local user
			FinishSessionCreation(bWasSuccessful ? EOnJoinSessionCompleteResult::Success : EOnJoinSessionCompleteResult::UnknownError);
		}
	}
}

void UScrapyardGameInstance::OnRegisterLocalPlayerComplete(const FUniqueNetId& PlayerId, EOnJoinSessionCompleteResult::Type Result)
{
	FinishSessionCreation(Result);
}

void UScrapyardGameInstance::FinishSessionCreation(EOnJoinSessionCompleteResult::Type Result)
{
	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		// Travel to the specified match URL
		GetWorld()->ServerTravel(TravelURL);
	}
	else
	{
		FText ReturnReason = NSLOCTEXT("NetworkErrors", "CreateSessionFailed", "Failed to create session.");
		FText OKButton = NSLOCTEXT("DialogButtons", "OKAY", "OK");
		ShowMessageThenGoMain(ReturnReason, OKButton, FText::GetEmpty());
	}
}

/** Callback which is intended to be called upon finding sessions */
void UScrapyardGameInstance::OnSearchSessionsComplete(bool bWasSuccessful)
{
	AScrapyardGameSession* const Session = GetGameSession();
	if (Session)
	{
		Session->OnFindSessionsComplete().Remove(OnSearchSessionsCompleteDelegateHandle);
	}
}

bool UScrapyardGameInstance::LoadFrontEndMap(const FString& MapName)
{
	bool bSuccess = true;

	// if already loaded, do nothing
	UWorld* const World = GetWorld();
	if (World)
	{
		FString const CurrentMapName = *World->PersistentLevel->GetOutermost()->GetName();
		//if (MapName.Find(TEXT("Highrise")) != -1)
		if (CurrentMapName == MapName)
		{
			return bSuccess;
		}
	}

	FString Error;
	EBrowseReturnVal::Type BrowseRet = EBrowseReturnVal::Failure;
	FURL URL(
		*FString::Printf(TEXT("%s"), *MapName)
		);

	if (URL.Valid && !HasAnyFlags(RF_ClassDefaultObject)) //CastChecked<UEngine>() will fail if using Default__ScrapyardGameInstance, so make sure that we're not default
	{
		BrowseRet = GetEngine()->Browse(*WorldContext, URL, Error);

		// Handle failure.
		if (BrowseRet != EBrowseReturnVal::Success)
		{
			UE_LOG(LogLoad, Fatal, TEXT("%s"), *FString::Printf(TEXT("Failed to enter %s: %s. Please check the log for errors."), *MapName, *Error));
			bSuccess = false;
		}
	}
	return bSuccess;
}

void UScrapyardGameInstance::SetPresenceForLocalPlayers(const FString& StatusStr, const FVariantData& PresenceData)
{
	const auto Presence = Online::GetPresenceInterface();
	if (Presence.IsValid())
	{
		for (int i = 0; i < LocalPlayers.Num(); ++i)
		{
			const TSharedPtr<const FUniqueNetId> UserId = LocalPlayers[i]->GetPreferredUniqueNetId();

			if (UserId.IsValid())
			{
				FOnlineUserPresenceStatus PresenceStatus;
				PresenceStatus.StatusStr = StatusStr;
				PresenceStatus.Properties.Add(DefaultPresenceKey, PresenceData);

				Presence->SetPresence(*UserId, PresenceStatus);
			}
		}
	}
}

void UScrapyardGameInstance::InternalTravelToSession(const FName& SessionName)
{
	APlayerController * const PlayerController = GetFirstLocalPlayerController();

	if ( PlayerController == nullptr )
	{
		FText ReturnReason = NSLOCTEXT("NetworkErrors", "InvalidPlayerController", "Invalid Player Controller");
		FText OKButton = NSLOCTEXT("DialogButtons", "OKAY", "OK");
		RemoveNetworkFailureHandlers();
		ShowMessageThenGoMain(ReturnReason, OKButton, FText::GetEmpty());
		return;
	}

	// travel to session
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

	if ( OnlineSub == nullptr )
	{
		FText ReturnReason = NSLOCTEXT("NetworkErrors", "OSSMissing", "OSS missing");
		FText OKButton = NSLOCTEXT("DialogButtons", "OKAY", "OK");
		RemoveNetworkFailureHandlers();
		ShowMessageThenGoMain(ReturnReason, OKButton, FText::GetEmpty());
		return;
	}

	FString URL;
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

	if ( !Sessions.IsValid() || !Sessions->GetResolvedConnectString( SessionName, URL ) )
	{
		FText FailReason = NSLOCTEXT("NetworkErrors", "TravelSessionFailed", "Travel to Session failed.");
		FText OKButton = NSLOCTEXT("DialogButtons", "OKAY", "OK");
		ShowMessageThenGoMain(FailReason, OKButton, FText::GetEmpty());
		UE_LOG(LogOnlineGame, Warning, TEXT("Failed to travel to session upon joining it"));
		return;
	}

	PlayerController->ClientTravel(URL, TRAVEL_Absolute);
}

void UScrapyardGameInstance::HandleSignInChangeMessaging()
{
	// Master user signed out, go to initial state (if we aren't there already)
	if ( CurrentState != GetInitialState() )
	{
		GotoInitialState();
	}
}

void UScrapyardGameInstance::HandleUserLoginChanged(int32 GameUserIndex, ELoginStatus::Type PreviousLoginStatus, ELoginStatus::Type LoginStatus, const FUniqueNetId& UserId)
{
	const bool bDowngraded = (LoginStatus == ELoginStatus::NotLoggedIn && GetOnlineMode() == EOnlineMode::Offline) || (LoginStatus != ELoginStatus::LoggedIn && GetOnlineMode() != EOnlineMode::Offline);

	UE_LOG( LogOnline, Log, TEXT( "HandleUserLoginChanged: bDownGraded: %i" ), (int)bDowngraded );

	TSharedPtr<GenericApplication> GenericApplication = FSlateApplication::Get().GetPlatformApplication();
	bIsLicensed = GenericApplication->ApplicationLicenseValid();

	// Find the local player associated with this unique net id
	ULocalPlayer * LocalPlayer = FindLocalPlayerFromUniqueNetId( UserId );

	LocalPlayerOnlineStatus[GameUserIndex] = LoginStatus;

	// If this user is signed out, but was previously signed in, punt to welcome (or remove splitscreen if that makes sense)
	if ( LocalPlayer != NULL )
	{
		if (bDowngraded)
		{
			UE_LOG( LogOnline, Log, TEXT( "HandleUserLoginChanged: Player logged out: %s" ), *UserId.ToString() );

			LabelPlayerAsQuitter(LocalPlayer);

			// Check to see if this was the master, or if this was a split-screen player on the client
			if ( LocalPlayer == GetFirstGamePlayer() || GetOnlineMode() != EOnlineMode::Offline )
			{
				HandleSignInChangeMessaging();
			}
			else
			{
				// Remove local split-screen players from the list
				RemoveExistingLocalPlayer( LocalPlayer );
			}
		}
	}
}

void UScrapyardGameInstance::HandleAppWillDeactivate()
{
	if (CurrentState == ScrapyardGameInstanceState::Playing)
	{
		// Just have the first player controller pause the game.
		UWorld* const GameWorld = GetWorld();
		if (GameWorld)
		{
			// protect against a second pause menu loading on top of an existing one if someone presses the Jewel / PS buttons.
			bool bNeedsPause = true;
			for (FConstControllerIterator It = GameWorld->GetControllerIterator(); It; ++It)
			{
				ARobotPlayerController* Controller = Cast<ARobotPlayerController>(*It);
				if (Controller && (Controller->IsPaused()))// || Controller->IsGameMenuVisible()))
				{
					bNeedsPause = false;
					break;
				}
			}

			if (bNeedsPause)
			{
				ARobotPlayerController* const Controller = Cast<ARobotPlayerController>(GameWorld->GetFirstPlayerController());
				if (Controller)
				{
				//	Controller->ShowInGameMenu();
				}
			}
		}
	}
}

void UScrapyardGameInstance::HandleAppSuspend()
{
	// Players will lose connection on resume. However it is possible the game will exit before we get a resume, so we must kick off round end events here.
	UE_LOG( LogOnline, Warning, TEXT( "UScrapyardGameInstance::HandleAppSuspend" ) );
	UWorld* const World = GetWorld(); 
//	ABattleGameState* const GameState = World != NULL ? World->GetGameState<ABattleGameState>() : NULL;

	if ( CurrentState != ScrapyardGameInstanceState::None && CurrentState != GetInitialState() )
	{
		UE_LOG( LogOnline, Warning, TEXT( "UScrapyardGameInstance::HandleAppSuspend: Sending round end event for players" ) );

		// Send round end events for local players
		for (int i = 0; i < LocalPlayers.Num(); ++i)
		{
			auto ScrapyardPC = Cast<ARobotPlayerController>(LocalPlayers[i]->PlayerController);
			if (ScrapyardPC)
			{
				// Assuming you can't win if you quit early
//				ScrapyardPC->ClientSendRoundEndEvent(false, GameState->ElapsedTime);
			}
		}
	}
}

void UScrapyardGameInstance::HandleAppResume()
{
	UE_LOG( LogOnline, Log, TEXT( "UScrapyardGameInstance::HandleAppResume" ) );

	if ( CurrentState != ScrapyardGameInstanceState::None && CurrentState != GetInitialState() )
	{
		UE_LOG( LogOnline, Warning, TEXT( "UScrapyardGameInstance::HandleAppResume: Attempting to sign out players" ) );

		for ( int32 i = 0; i < LocalPlayers.Num(); ++i )
		{
			if ( LocalPlayers[i]->GetCachedUniqueNetId().IsValid() && LocalPlayerOnlineStatus[i] == ELoginStatus::LoggedIn && !IsLocalPlayerOnline( LocalPlayers[i] ) )
			{
				UE_LOG( LogOnline, Log, TEXT( "UScrapyardGameInstance::HandleAppResume: Signed out during resume." ) );
				HandleSignInChangeMessaging();
				break;
			}
		}
	}
}

void UScrapyardGameInstance::HandleAppLicenseUpdate()
{
	TSharedPtr<GenericApplication> GenericApplication = FSlateApplication::Get().GetPlatformApplication();
	bIsLicensed = GenericApplication->ApplicationLicenseValid();
}

void UScrapyardGameInstance::HandleSafeFrameChanged()
{
	UCanvas::UpdateAllCanvasSafeZoneData();
}

bool UScrapyardGameInstance::HandleOpenCommand(const TCHAR* Cmd, FOutputDevice& Ar, UWorld* InWorld)
{
	bool const bOpenSuccessful = Super::HandleOpenCommand(Cmd, Ar, InWorld);
	if (bOpenSuccessful)
	{
		GotoState(ScrapyardGameInstanceState::Playing);
	}

	return bOpenSuccessful;
}
