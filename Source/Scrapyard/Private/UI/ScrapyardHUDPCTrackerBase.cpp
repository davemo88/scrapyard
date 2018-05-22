// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

//#include "ScrapyardGame.h"
#include "ScrapyardHUDPCTrackerBase.h"


/** Initialize with a world context. */
void ScrapyardHUDPCTrackerBase::Init( const FLocalPlayerContext& InContext )
{
	Context = InContext;
}

//TWeakObjectPtr<AScrapyardPlayerController> ScrapyardHUDPCTrackerBase::GetPlayerController() const
//{
//	if ( ensureMsgf( Context.IsValid(), TEXT("Game context must be initialized!") ) )
//	{
//		APlayerController* PC = Context.GetPlayerController();
//		AScrapyardPlayerController* ScrapyardPC = Cast<AScrapyardPlayerController>(PC);
//		return TWeakObjectPtr<AScrapyardPlayerController>(ScrapyardPC);
//	}
//	else
//	{
//		return NULL;
//	}
//}


UWorld* ScrapyardHUDPCTrackerBase::GetWorld() const
{
	if ( ensureMsgf( Context.IsValid(), TEXT("Game context must be initialized!") ) )
	{
		return Context.GetWorld();
	}
	else
	{
		return NULL;
	}
}

//AScrapyardGameState* ScrapyardHUDPCTrackerBase::GetGameState() const
AGameState* ScrapyardHUDPCTrackerBase::GetGameState() const
{
	if ( ensureMsgf( Context.IsValid(), TEXT("Game context must be initialized!") ) )
	{
//		return Context.GetWorld()->GetGameState<AScrapyardGameState>();
		return NULL;
	}
	else
	{
		return NULL;
	}
}

const FLocalPlayerContext& ScrapyardHUDPCTrackerBase::GetContext() const
{
	return Context;
}



