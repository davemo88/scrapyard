#pragma once
#include "Online.h"

class FScrapyardOnlineSessionSettings : public FOnlineSessionSettings
{
public:

	FScrapyardOnlineSessionSettings(bool bIsLAN = false, bool bIsPresence = false, int32 MaxNumPlayers = 4);
	virtual ~FScrapyardOnlineSessionSettings() {}
};

/**
 * General search setting for a Scrapyard game
 */
class FScrapyardOnlineSearchSettings : public FOnlineSessionSearch
{
public:
	FScrapyardOnlineSearchSettings(bool bSearchingLAN = false, bool bSearchingPresence = false);

	virtual ~FScrapyardOnlineSearchSettings() {}
};

/**
 * Search settings for an empty dedicated server to host a match
 */
class FScrapyardOnlineSearchSettingsEmptyDedicated : public FScrapyardOnlineSearchSettings
{
public:
	FScrapyardOnlineSearchSettingsEmptyDedicated(bool bSearchingLAN = false, bool bSearchingPresence = false);

	virtual ~FScrapyardOnlineSearchSettingsEmptyDedicated() {}
};