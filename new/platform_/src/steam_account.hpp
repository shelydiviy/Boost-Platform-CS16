#pragma once
#ifndef _STEAM_ACCOUNT
#define _STEAM_ACCOUNT

#include "steamtypes.h"
#include "network.hpp"
#include <netinet/in.h>
#include <sys/socket.h>
#include "steamclientpublic.h"

struct SteamAccount
{
public:
	SteamAccount(uint64 steamid, sockaddr_in socket_addr, socklen_t socket_len);
	SteamAccount(const SteamAccount&) = delete;
	SteamAccount(SteamAccount&&) = delete;

	sockaddr_in* GetAddrStruct();
	socklen_t* GetAddrSize();

	SteamAccountState GetState() const;
	CSteamID* GetSteamID() const;
	void SetState(SteamAccountState state);
	int m_Tries;

private:
	CSteamID* m_SteamID;
	SteamAccountState m_State;

	sockaddr_in m_SocketAddrStruct;
	socklen_t m_SocketAddrSize;
};

#endif