#ifndef _FAKE_SERVER
#define _FAKE_SERVER
#pragma once

#include <vector>
#include <cstdint>
#include <thread>
#include "socket.hpp"
#include "masterserver.hpp"
#include "data_parser.hpp"
#include "steam_gameserver.h"
#include "steam_account.hpp"
#include "steam_account_pool.hpp"
#include "client.hpp"
#include "mutex"

class MasterServer;
class Socket;
class Client;
struct SteamAccount;
struct SteamAccountPool;

//opcodes
typedef enum {
	A2S_INFO = 0x54, // Game client it's querying game server info
	A2S_CHALLANGE = 0x67
} ValvePacketOpcode;

class FakeServer
{
public:
	FakeServer(uint16 port, uint16 masterserver_port);
	FakeServer(const FakeServer&) = delete;
	FakeServer(FakeServer&&) = delete;
	~FakeServer();

	void ListenSocket();
	void StartListening();
	uint16* GetPort();

	void BuildPackets();
	void ManagePlayerPacket(CDataParser* data, int datalen);
	void ManageSteamFakerPacket(CDataParser* data);

	void NotifySteamFakerClientDisconnect(uint64 steamid, EDenyReason deny_reason, char reason_text[128]);
	void NotifySteamFakerClientConnect(uint64 steamid);
	void SetSteamID(uint64 steamid);

private:
	Socket* m_Socket;
	
	MasterServer* m_MasterServer;
	uint64 m_SteamID;

	SteamAccountPool* m_AccountsPool;

	CDataParser* m_QueryPacket;
	CDataParser* m_SecondQueryPacket;

	uint16 m_GamePort;
	uint16 m_MasterServerPort;
	byte m_Players = 31;

	std::vector<Client*> m_Clients;
	std::mutex m_ClientVMutex;

	bool m_Packets;
};
#endif