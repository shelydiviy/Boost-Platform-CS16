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

	void Init(int16_t port, int16_t game_port);
	void ListenSocket();
	bool LoginUser(uint32 ip, unsigned char* steam_key, uint32 steam_key_size, CSteamID* user_steam);

private:
	Socket* m_Socket;

	int16_t m_Port;
	int16_t m_GamePort;
};

#endif