#ifndef _PLATFORM_MANAGER
#define _PLATFORM_MANAGER

#include <thread>
#include <vector>
#include "socket.hpp"
#include "fake_server.hpp"
#include "data_parser.hpp"
#include "chrono"
#include "steam_gameserver.h"
#include "mutex"
#include "semaphore"

class FakeServer;
class CSteam3Server;

class PlatformManager
{
public:
    PlatformManager();
    PlatformManager(const PlatformManager&) = delete;
    PlatformManager(PlatformManager&&) = delete;
    ~PlatformManager();

    static PlatformManager* get();
    void RegisterSteamCallbacks();
    void StartSteamCallbacksThread();
    void StartFakeServers(int total_number_of_servers);

    void SteamLogOnSuccess();
    void SteamLonOnFailure(EResult result);
    void SteamOnGSClientDeny(uint64 steamid, EDenyReason deny_reason, char reason_text[128]);
    void SteamOnGSClientApprove(uint64 steamid);

private:
    static PlatformManager* m_Platform;
    void RunCallbacks();

    CSteam3Server* m_Steam3Server;
    FakeServer* m_FakeServer;
    std::thread m_SteamCallbacksThread;

    std::mutex m_SteamAccountsMutex;
    std::binary_semaphore m_SteamFakeServerRegistrationSemaphore {0};
};

#endif
