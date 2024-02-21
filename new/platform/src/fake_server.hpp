#ifndef _FAKE_SERVER
#define _FAKE_SERVER
#pragma once

#include <cstdint>
#include <thread>
#include "socket.hpp"
#include "masterserver.hpp"
#include "data_parser.hpp"
#include <cstddef>

//opcodes
typedef enum {
	QUERY_ENGINE = 0x54,
	CVAR_LIST = 0x56,
	INVALID = 0x00
} PacketType;


class FakeServer
{
public:
	FakeServer(int16_t port, int16_t master_server_port);
	FakeServer(const FakeServer&) = delete;
	FakeServer(FakeServer&&) = delete;
	
	void ListenSocket();
	void BuildPackets();
	PacketType GetMessageType(CDataParser* data);
	void IncreasePlayers();
	void DecreasePlayers();

private:
	Socket* m_Socket;
	MasterServer* m_MasterServer;

	CDataParser* m_QueryPacket;

	int16_t m_GamePort;
	int16_t m_MasterServerPort;
	byte m_Players = 1;
};
#endif