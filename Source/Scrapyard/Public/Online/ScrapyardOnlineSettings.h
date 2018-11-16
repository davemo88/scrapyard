#pragma once
#include "Online.h"

class FScrapyardOnlineSessionSettings : public FOnlineSessionSettings
{
public:

  FScrapyardOnlineSessionSettings(bool bIsLAN = true, bool bIsPresence = true, int32 MaxNumPlayers = 4);
  virtual ~FScrapyardOnlineSessionSettings() {}
};

class FScrapyardOnlineSessionSearch : public FOnlineSessionSearch
{
public:
  FScrapyardOnlineSessionSearch(bool bSearchingLAN = true, bool bSearchingPresence = true);
  virtual ~FScrapyardOnlineSessionSearch() {}
};
