// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrapyardPlayerController.h"

#include "Robots/RobotCharacter.h"
//#include "Online/ScrapyardPlayerState.h"
//#include "UI/Menu/ScrapyardIngameMenu.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/PlayerController.h"
#include "Online.h"
#include "Public/Misc/PackageName.h"
#include "OnlineEventsInterface.h"
#include "OnlineIdentityInterface.h"
#include "OnlineSessionInterface.h"
#include "ScrapyardGameInstance.h"
//#include "AudioThread.h"

AScrapyardPlayerController::AScrapyardPlayerController()
{
	bAllowGameActions = true;
	bGameEndedFrame = false;
	bHasSentStartEvents = false;

	ServerSayString = TEXT("Say");

}

void AScrapyardPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// UI input
//	InputComponent->BindAction("InGameMenu", IE_Pressed, this, &AScrapyardPlayerController::OnToggleInGameMenu);

	// voice chat
//	InputComponent->BindAction("PushToTalk", IE_Pressed, this, &APlayerController::StartTalking);
//	InputComponent->BindAction("PushToTalk", IE_Released, this, &APlayerController::StopTalking);

//	InputComponent->BindAction("ToggleChat", IE_Pressed, this, &AScrapyardPlayerController::ToggleChatWindow);
}


void AScrapyardPlayerController::SetPlayer( UPlayer* InPlayer )
{
	Super::SetPlayer( InPlayer );

	if (ULocalPlayer* const LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		//Build menu only after game is initialized
//		ScrapyardIngameMenu = MakeShareable(new FScrapyardIngameMenu());
//		ScrapyardIngameMenu->Construct(Cast<ULocalPlayer>(Player));

		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
	}
}

void AScrapyardPlayerController::UnFreeze()
{
	ServerRestartPlayer();
}

void AScrapyardPlayerController::FailedToSpawnPawn()
{
	if(StateName == NAME_Inactive)
	{
		BeginInactiveState();
	}
	Super::FailedToSpawnPawn();
}

//void AScrapyardPlayerController::OnToggleInGameMenu()
//{
//	if( GEngine->GameViewport == nullptr )
//	{
//		return;
//	}

//	// this is not ideal, but necessary to prevent both players from pausing at the same time on the same frame
//	UWorld* GameWorld = GEngine->GameViewport->GetWorld();

//	for(auto It = GameWorld->GetControllerIterator(); It; ++It)
//	{
//		AScrapyardPlayerController* Controller = Cast<AScrapyardPlayerController>(*It);
//		if(Controller && Controller->IsPaused())
//		{
//			return;
//		}
//	}

//	// if no one's paused, pause
//	if (ScrapyardIngameMenu.IsValid())
//	{
//		ScrapyardIngameMenu->ToggleGameMenu();
//	}
//}

//bool AScrapyardPlayerController::IsGameMenuVisible() const
//{
//	bool Result = false; 
//	if (ScrapyardIngameMenu.IsValid())
//	{
//		Result = ScrapyardIngameMenu->GetIsGameMenuUp();
//	} 

//	return Result;
//}

void AScrapyardPlayerController::SetIsVibrationEnabled(bool bEnable)
{
	bIsVibrationEnabled = bEnable;
}

void AScrapyardPlayerController::ClientGameStarted_Implementation()
{
	bAllowGameActions = true;

	// Enable controls mode now the game has started
	SetIgnoreMoveInput(false);

	bGameEndedFrame = false;

	// Send round start event
	const auto Events = Online::GetEventsInterface();
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);

	if(LocalPlayer != nullptr && Events.IsValid())
	{
		auto UniqueId = LocalPlayer->GetPreferredUniqueNetId();

		if (UniqueId.IsValid())
		{
			// Generate a new session id
			Events->SetPlayerSessionId(*UniqueId, FGuid::NewGuid());

			FString MapName = *FPackageName::GetShortName(GetWorld()->PersistentLevel->GetOutermost()->GetName());

			// Fire session start event for all cases
			FOnlineEventParms Params;
			Params.Add( TEXT( "GameplayModeId" ), FVariantData( (int32)1 ) ); // @todo determine game mode (ffa v tdm)
			Params.Add( TEXT( "DifficultyLevelId" ), FVariantData( (int32)0 ) ); // unused
			Params.Add( TEXT( "MapName" ), FVariantData( MapName ) );
			
			Events->TriggerEvent(*UniqueId, TEXT("PlayerSessionStart"), Params);

			// Online matches require the MultiplayerRoundStart event as well
			UScrapyardGameInstance* SGI = GetWorld() != NULL ? Cast<UScrapyardGameInstance>(GetWorld()->GetGameInstance()) : NULL;

// TODO add this to game instance
			if (false)//SGI->GetOnlineMode() == EOnlineMode::Online)
			{
				FOnlineEventParms MultiplayerParams;

				// @todo: fill in with real values
				MultiplayerParams.Add( TEXT( "SectionId" ), FVariantData( (int32)0 ) ); // unused
				MultiplayerParams.Add( TEXT( "GameplayModeId" ), FVariantData( (int32)1 ) ); // @todo determine game mode (ffa v tdm)
				MultiplayerParams.Add( TEXT( "MatchTypeId" ), FVariantData( (int32)1 ) ); // @todo abstract the specific meaning of this value across platforms
				MultiplayerParams.Add( TEXT( "DifficultyLevelId" ), FVariantData( (int32)0 ) ); // unused
				
				Events->TriggerEvent(*UniqueId, TEXT("MultiplayerRoundStart"), MultiplayerParams);
			}

			bHasSentStartEvents = true;
		}
	}
}

/** Starts the online game using the session name in the PlayerState */
void AScrapyardPlayerController::ClientStartOnlineGame_Implementation()
{
	if (!IsPrimaryPlayer())
		return;

//	AScrapyardPlayerState* ScrapyardPlayerState = Cast<AScrapyardPlayerState>(PlayerState);
	APlayerState* ScrapyardPlayerState = Cast<APlayerState>(PlayerState);
	if (ScrapyardPlayerState)
	{
		IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
		if (OnlineSub)
		{
			IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
			if (Sessions.IsValid())
			{
				UE_LOG(LogOnline, Log, TEXT("Starting session %s on client"), *ScrapyardPlayerState->SessionName.ToString() );
				Sessions->StartSession(ScrapyardPlayerState->SessionName);
			}
		}
	}
	else
	{
		// Keep retrying until player state is replicated
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ClientStartOnlineGame, this, &AScrapyardPlayerController::ClientStartOnlineGame_Implementation, 0.2f, false);
	}
}

/** Ends the online game using the session name in the PlayerState */
void AScrapyardPlayerController::ClientEndOnlineGame_Implementation()
{
	if (!IsPrimaryPlayer())
		return;

//	AScrapyardPlayerState* ScrapyardPlayerState = Cast<AScrapyardPlayerState>(PlayerState);
	APlayerState* ScrapyardPlayerState = Cast<APlayerState>(PlayerState);
	if (ScrapyardPlayerState)
	{
		IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
		if (OnlineSub)
		{
			IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
			if (Sessions.IsValid())
			{
				UE_LOG(LogOnline, Log, TEXT("Ending session %s on client"), *ScrapyardPlayerState->SessionName.ToString() );
				Sessions->EndSession(ScrapyardPlayerState->SessionName);
			}
		}
	}
}

void AScrapyardPlayerController::HandleReturnToMainMenu()
{
	CleanupSessionOnReturnToMenu();
}

void AScrapyardPlayerController::ClientReturnToMainMenu_Implementation(const FString& InReturnReason)
{		
	UScrapyardGameInstance* SGI = GetWorld() != NULL ? Cast<UScrapyardGameInstance>(GetWorld()->GetGameInstance()) : NULL;

	if ( !ensure( SGI != NULL ) )
	{
		return;
	}

	if ( GetNetMode() == NM_Client )
	{
		const FText ReturnReason	= NSLOCTEXT( "NetworkErrors", "HostQuit", "The host has quit the match." );
		const FText OKButton		= NSLOCTEXT( "DialogButtons", "OKAY", "OK" );

// TODO: actually do something here?
//		SGI->ShowMessageThenGotoState( ReturnReason, OKButton, FText::GetEmpty(), ScrapyardGameInstanceState::MainMenu );
	}
	else
	{
//		SGI->GotoState(ScrapyardGameInstanceState::MainMenu);
	}

	// Clear the flag so we don't do normal end of round stuff next
	bGameEndedFrame = false;
}

/** Ends and/or destroys game session */
void AScrapyardPlayerController::CleanupSessionOnReturnToMenu()
{
	UScrapyardGameInstance * SGI = GetWorld() != NULL ? Cast<UScrapyardGameInstance>( GetWorld()->GetGameInstance() ) : NULL;

	if ( ensure( SGI != NULL ) )
	{
//		SGI->CleanupSessionOnReturnToMenu();
	}
}

void AScrapyardPlayerController::ClientGameEnded_Implementation(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::ClientGameEnded_Implementation(EndGameFocus, bIsWinner);
	
	// Disable controls now the game has ended
	SetIgnoreMoveInput(true);

	bAllowGameActions = false;

	// Make sure that we still have valid view target
	SetViewTarget(GetPawn());

	// Flag that the game has just ended (if it's ended due to host loss we want to wait for ClientReturnToMainMenu_Implementation first, incase we don't want to process)
	bGameEndedFrame = true;
}

bool AScrapyardPlayerController::IsMoveInputIgnored() const
{
	if (IsInState(NAME_Spectating))
	{
		return false;
	}
	else
	{
		return Super::IsMoveInputIgnored();
	}
}

bool AScrapyardPlayerController::IsLookInputIgnored() const
{
	if (IsInState(NAME_Spectating))
	{
		return false;
	}
	else
	{
		return Super::IsLookInputIgnored();
	}
}

void AScrapyardPlayerController::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
}

void AScrapyardPlayerController::Suicide()
{
	if ( IsInState(NAME_Playing) )
	{
		ServerSuicide();
	}
}

bool AScrapyardPlayerController::ServerSuicide_Validate()
{
	return true;
}

void AScrapyardPlayerController::ServerSuicide_Implementation()
{
	if ( (GetPawn() != NULL) && ((GetWorld()->TimeSeconds - GetPawn()->CreationTime > 1) || (GetNetMode() == NM_Standalone)) )
	{
		ARobotCharacter* MyPawn = Cast<ARobotCharacter>(GetPawn());
		if (MyPawn)
		{
// TODO: implement
//			MyPawn->Suicide();
		}
	}
}

bool AScrapyardPlayerController::IsVibrationEnabled() const
{
	return bIsVibrationEnabled;
}

bool AScrapyardPlayerController::IsGameInputAllowed() const
{
	return bAllowGameActions && !bCinematicMode;
}

void AScrapyardPlayerController::Say( const FString& Msg )
{
	ServerSay(Msg.Left(128));
}

bool AScrapyardPlayerController::ServerSay_Validate( const FString& Msg )
{
	return true;
}

void AScrapyardPlayerController::ServerSay_Implementation( const FString& Msg )
{
// TODO: implement
//	GetWorld()->GetAuthGameMode<AScrapyardGameMode>()->Broadcast(this, Msg, ServerSayString);
}


//void AScrapyardPlayerController::ShowInGameMenu()
//{
//	if(ScrapyardIngameMenu.IsValid() && !ScrapyardIngameMenu->GetIsGameMenuUp())
//	{
//		ScrapyardIngameMenu->ToggleGameMenu();
//	}
//}



