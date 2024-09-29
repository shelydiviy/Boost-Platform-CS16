#include "platform_manager.hpp"
#include "globals.hpp"
#include <arpa/inet.h>

PlatformManager* PlatformManager::m_Platform;

PlatformManager::PlatformManager() {}
PlatformManager::~PlatformManager() {}

void PlatformManager::RegisterSteamCallbacks()
{
	m_Steam3Server = new CSteam3Server();
	Console::get()->Printf("[PlatformManager] Registered SteamGameServerAPI callbacks\n");
}

void PlatformManager::StartSteamCallbacksThread()
{
	m_SteamCallbacksThread = std::thread(&PlatformManager::RunCallbacks, this);
	m_SteamCallbacksThread.detach();
}

PlatformManager* PlatformManager::get()
{
	if (m_Platform == nullptr)
	{
		m_Platform = new PlatformManager();
	}

	return m_Platform;
}

void PlatformManager::RunCallbacks()
{
	Console::get()->Printf("[PlatformManager] Starting to run SteamGameSeverAPI callbacks\n");

	while (true)
	{
		SteamGameServer_RunCallbacks();

		std::this_thread::sleep_for(std::chrono::milliseconds(STEAM_CALLBACKS_MILLISECOONDS));
	}
}

void PlatformManager::StartFakeServers(int total_number_of_servers)
{
	const int iStartGamePort = 27015;
	const int iStartMasterserverPort = 26000;

	for (int i = 0; i < total_number_of_servers; i++) {

		m_FakeServer = new FakeServer(iStartGamePort + i, iStartMasterserverPort + i);
	
		m_SteamFakeServerRegistrationSemaphore.acquire();

		m_FakeServer->StartListening();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void PlatformManager::SteamLogOnSuccess()
{
	m_FakeServer->SetSteamID(SteamGameServer()->GetSteamID().ConvertToUint64());
	Console::get()->Printf("[PlatformManager] Server %s:%i connected succesfully to Steam servers\n", IPV4_ADDRESS, *m_FakeServer->GetPort());

	m_SteamFakeServerRegistrationSemaphore.release();
}

void PlatformManager::SteamLonOnFailure(EResult result)
{
	Console::get()->Printf("[PlatformManager] Failed to register server in Valve masterserver\n");
}

void PlatformManager::SteamOnGSClientDeny(uint64 steamid, EDenyReason deny_reason, char reason_text[128])
{

	m_FakeServer->NotifySteamFakerClientDisconnect(steamid, deny_reason, reason_text);
}

void PlatformManager::SteamOnGSClientApprove(uint64 steamid)
{
	Console::get()->Printf("[PlatformManager] Account with SteamID %llu validated succesfully in Steam servers\n", steamid);
	m_FakeServer->NotifySteamFakerClientConnect(steamid);
}