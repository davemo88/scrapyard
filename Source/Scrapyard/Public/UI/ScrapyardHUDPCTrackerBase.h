// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/LocalPlayer.h"


/**
 * Helps HUD widgets know their context within the game world.
 * e.g. Is this a widget for player 1 or player 2?
 * e.g. In case of multiple PIE sessions, which world do I belong to?
 */
class ScrapyardHUDPCTrackerBase
{
public:

	virtual ~ScrapyardHUDPCTrackerBase(){}

	/** Initialize with a world context. */
	void Init( const FLocalPlayerContext& InContext );

	/** Returns a pointer to the player controller */
//	TWeakObjectPtr<class AScrapyardPlayerController> GetPlayerController() const;
//	TWeakObjectPtr<class APlayerController> GetPlayerController() const;

	/** Returns a pointer to the World. (Via Player Controller) */
	UWorld* GetWorld() const;

	/** Get the current game GameState */
//	class AScrapyardGameState* GetGameState() const;
	class AGameState* GetGameState() const;

	/** @return the game world context */
	const FLocalPlayerContext& GetContext() const;

private:
	/** Which player and world this piece of UI belongs to. This is necessary to support  */
	FLocalPlayerContext Context;

};