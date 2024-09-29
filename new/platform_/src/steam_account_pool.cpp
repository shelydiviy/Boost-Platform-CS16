#include "steam_account_pool.hpp"
#include <sys/socket.h>

SteamAccountPool::SteamAccountPool()
{}

SteamAccountPool::~SteamAccountPool()
{
	for (SteamAccount* account : m_SteamAccounts)
	{
		delete account;
	}

	m_SteamAccounts.clear();
}

int SteamAccountPool::AddAccount(uint64 steamid, sockaddr_in socket_addr, socklen_t socket_len)
{
	std::unique_lock<std::mutex>lock(m_Mutex);
	
	SteamAccount* account = new SteamAccount(steamid, socket_addr, socket_len);

	m_SteamAccounts.push_back(account);
	
	return static_cast<int>(m_SteamAccounts.size() - 1);
}

SteamAccount* SteamAccountPool::GetAccount(uint64 steamid)
{
	std::unique_lock<std::mutex>lock(m_Mutex);

	for (SteamAccount* account : m_SteamAccounts)
	{
		if (account->GetSteamID()->ConvertToUint64() == steamid)
			return account;
	}

	return nullptr;
}
