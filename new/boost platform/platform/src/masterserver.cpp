#include "masterserver.hpp"
#include "globals.hpp"

MasterServer::MasterServer() {}

MasterServer::~MasterServer()
{
	SteamGameServer_Shutdown();
}

bool MasterServer::Init(uint16 port, uint16 game_port)
{
	m_Port = port;
	m_GamePort = game_port;

	if (!SteamGameServer_Init(UINT32_IP, m_Port, m_GamePort, 0xFFFFu, eServerModeAuthenticationAndSecure, "1.1.2.7"))
	{
		Console::get()->Printf("[CRITICAL] [MasterServer] Failed to init SteamGameServer for %s:%i.\n", IPV4_ADDRESS, m_GamePort);
		return false;
	}
	else Console::get()->Printf("[MasterServer] Succesfully sent fake game server ticket registration to Steam servers\n");
	
	if (!SteamGameServer())
	{
		Console::get()->Printf("[MasterServer] SteamGameServer interface not initialized.\n");
		return false;
	}

	SteamGameServer()->SetProduct("cstrike");
	SteamGameServer()->SetModDir("cstrike");
	SteamGameServer()->SetDedicatedServer(true);
	SteamGameServer()->SetGameDescription("Counter-Strike");
	SteamGameServer()->SetMaxPlayerCount(32);
	SteamGameServer()->SetBotPlayerCount(0);
	SteamGameServer()->SetServerName("CS.MUIE.RO");
	SteamGameServer()->SetMapName("_aa");
	SteamGameServer()->SetPasswordProtected(false);
	SteamGameServer()->SetKeyValue("protocol", "48");

	SteamGameServer()->LogOnAnonymous();
	
	SteamGameServer()->EnableHeartbeats(true);
	SteamGameServer()->SetHeartbeatInterval(400);

	SteamGameServer()->ForceHeartbeat();

	//SteamGameServer()->CreateUnauthenticatedUserConnection();
	//SteamGameServer()->SetBotPlayerCount(1);

	Console::get()->Printf("[MasterServer] Sended fake game server details to Steam servers.\n");

	return true;
}

bool MasterServer::LoginUser(uint32 ip, unsigned char* steam_key, uint32 steam_key_size, CSteamID* steamid)
{
	return SteamGameServer()->SendUserConnectAndAuthenticate(ip, steam_key, steam_key_size, steamid);
}

void MasterServer::DisconnectUser(CSteamID* steamid)
{
	SteamGameServer()->SendUserDisconnect(*steamid);
}

uint64 MasterServer::GetSteamID()
{
	return SteamGameServer()->GetSteamID().ConvertToUint64();
}