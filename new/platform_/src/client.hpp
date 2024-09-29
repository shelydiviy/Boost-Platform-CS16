#pragma once
#ifndef _CLIENT
#define _CLIENT

#include "steamtypes.h"
#include "socket.hpp"
#include "sys/socket.h"
#include "netinet/in.h"
#include "thread"
#include "data_parser.hpp"
#include "globals.hpp"

class Client
{
public:
	Client(Socket* fake_game_server_socket, const sockaddr_in* socket, const socklen_t* socklen);
	Client(const Client&) = delete;
	Client(Client&&) = delete;

	~Client();

	void ListenClientSocket();
	void SendPacket(unsigned char* buffer, int bufferlen);
	int16 GetClientPort();
	sockaddr_in* GetClientAddr();

private:
	
	bool m_ShouldRun;
	char* m_IPv4Address;
	uint16 m_Port;

	std::thread m_ClientThread;

	Socket* m_BridgeSocket;
	Socket* m_FakeGameServerSocket;

	sockaddr_in m_ClientSockAddr;
	socklen_t m_ClientSockLen;

	sockaddr_in m_GameServerSockAddr;
	socklen_t m_GameServerSockLen;
};

#endif