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
class FScrapyardOnlineSessionSearch : public FOnlineSessionSearch
{
public:
	FScrapyardOnlineSessionSearch(bool bSearchingLAN = false, bool bSearchingPresence = false);

	virtual ~FScrapyardOnlineSessionSearch() {}
};