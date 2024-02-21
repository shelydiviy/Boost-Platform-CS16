#include "masterserver.hpp"
#include "globals.hpp"
#include "sv_steam3.hpp"

MasterServer::MasterServer()
{}

void MasterServer::Init(int16_t port, int16_t game_port)
{
	m_Port = port;
	m_GamePort = game_port;

	struct in_addr addr;
	if (inet_pton(AF_INET, IPV4_ADDRESS, &addr) != 1) {
		Printf("Failed to convert IPv4 from string to uint32");
		return;
	}

	// Convert the binary form to network byte order
	uint32 unIP = ntohl(addr.s_addr);

	Printf("Initializing SteamGameServer at %s:%i [GamePort: %i]\n", IPV4_ADDRESS, m_Port, m_GamePort);

	if(!SteamGameServer_Init(unIP, m_Port, m_GamePort, 0xFFFFu, eServerModeAuthentication, "1.1.2.7"))
	{
		Printf("[CRITICAL] Failed to init SteamGameServer for %s:%i.\n", IPV4_ADDRESS, m_GamePort);
		return;
	}
	
	if (!SteamGameServer())
	{
		Printf("SteamGameServer doesn't exists\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		Printf("SteamGameServer has been initialized succesfuly for server %s:%i\n", IPV4_ADDRESS, m_GamePort);
	}

	//std::thread(&MasterServer::ListenSocket, this).detach();

	SteamGameServer()->SetProduct("cstrike");
	SteamGameServer()->SetModDir("cstrike");
	SteamGameServer()->SetDedicatedServer(true);
	SteamGameServer()->SetGameDescription("cacat");
	SteamGameServer()->SetMaxPlayerCount(32);
	SteamGameServer()->SetBotPlayerCount(0);
	SteamGameServer()->SetServerName("CACAT");
	SteamGameServer()->SetMapName("_aa");
	SteamGameServer()->SetPasswordProtected(false);
	
	SteamGameServer()->LogOnAnonymous();
	SteamGameServer_RunCallbacks();
	
	SteamGameServer()->EnableHeartbeats(true);
	SteamGameServer()->SetHeartbeatInterval(400);
	SteamGameServer()->SetKeyValue("protocol", "48");

	SteamGameServer()->ForceHeartbeat();

	//SteamGameServer_Shutdown();
}

void MasterServer::ListenSocket()
{
	char buffer[MAX_SOCKET_BUFFER_LENGTH];
	uint32 unIP = 0;
	uint16 unPort = 0;

	char secondBuffer[MAX_SOCKET_BUFFER_LENGTH];
	int iLen, i;

	while (true)
	{
		SteamGameServer_RunCallbacks();
		iLen = SteamGameServer()->GetNextOutgoingPacket(buffer, sizeof(buffer), &unIP, &unPort);

		if(iLen > 0)
		{
			Printf("Received %s", buffer);
			while (iLen)
			{
				secondBuffer[i] = *buffer;
				iLen = SteamGameServer()->GetNextOutgoingPacket(buffer, sizeof(buffer), &unIP, &unPort);
				i++;
			}

			secondBuffer[i] = 0x00;
			i = 0;

			Printf("[MS] %s:%i -> %s\n", IPV4_ADDRESS, m_GamePort, secondBuffer);
		}
	}
}

bool MasterServer::LoginUser(uint32 ip, unsigned char* steam_key, uint32 steam_key_size, CSteamID* user_steam)
{
	return SteamGameServer()->SendUserConnectAndAuthenticate(ip, steam_key, steam_key_size, user_steam);
}
