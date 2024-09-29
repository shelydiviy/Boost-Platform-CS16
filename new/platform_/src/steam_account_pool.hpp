#pragma once
#ifndef _STEAM_ACCOUNT_POOL
#define _STEAM_ACCOUNT_POOL

#include "mutex"
#include "vector"
#include "steam_account.hpp"

struct SteamAccount;

struct SteamAccountPool
{
public:
	SteamAccountPool();
	SteamAccountPool(const SteamAccountPool&) = delete;
	SteamAccountPool(SteamAccountPool&&) = delete;
	~SteamAccountPool();

	// Adding an account and returning it's index
	int AddAccount(uint64 steamid, sockaddr_in socket_addr, socklen_t socket_len);
	SteamAccount* GetAccount(uint64 steamid);

private:
	std::mutex m_Mutex;
	std::vector<SteamAccount*> m_SteamAccounts;
};

#endif