#ifndef _MASTERSERVER
#define _MASTERSERVER

#include "sv_steam3.hpp"
#include <cstdint>
#include <arpa/inet.h>
#include "socket.hpp"

class MasterServer
{
public:
	MasterServer();
	MasterServer(const MasterServer&) = delete;
	MasterServer(MasterServer&&) = delete;
	~MasterServer();

	bool Init(uint16 port, uint16 game_port);
	bool LoginUser(uint32 ip, unsigned char* steam_key, uint32 steam_key_size, CSteamID* steamid);
	void DisconnectUser(CSteamID* steamid);
	uint64 GetSteamID();

private:
	uint16 m_Port;
	uint16 m_GamePort;
};

#endif