#include "steam_account.hpp"

SteamAccount::SteamAccount(uint64 steamid, sockaddr_in socket_addr, socklen_t socket_len) :
	m_SteamID(new CSteamID(steamid)),
	m_State(REQUEST_CONNECT),
	m_SocketAddrStruct(socket_addr),
	m_SocketAddrSize(socket_len) {}

SteamAccountState SteamAccount::GetState() const
{
	return m_State;
}

CSteamID* SteamAccount::GetSteamID() const
{
	return m_SteamID;
}

void SteamAccount::SetState(SteamAccountState state)
{
	m_State = state;
}

sockaddr_in* SteamAccount::GetAddrStruct()
{
	return &m_SocketAddrStruct;
}

socklen_t* SteamAccount::GetAddrSize()
{
	return &m_SocketAddrSize;
}