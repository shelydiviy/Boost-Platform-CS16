#ifndef _STEAM_SERVER
#define _STEAM_SERVER

#include <steam_api.h>
#include <steam_gameserver.h>
#include "globals.hpp"

class CSteam3Server
{
protected:
    bool m_bHasActivePlayers;
    bool m_bWantToBeSecure;
    bool m_bLanOnly;
    CSteamID m_SteamIDGS;

public:
    CSteam3Server() :
        m_CallbackGSClientApprove(this, &CSteam3Server::OnGSClientApprove),
        m_CallbackGSClientDeny(this, &CSteam3Server::OnGSClientDeny),
        m_CallbackGSClientKick(this, &CSteam3Server::OnGSClientKick),
        m_CallbackGSPolicyResponse(this, &CSteam3Server::OnGSPolicyResponse),
        m_CallbackLogonSuccess(this, &CSteam3Server::OnLogonSuccess),
        m_CallbackLogonFailure(this, &CSteam3Server::OnLogonFailure),
        m_SteamIDGS(1, 0, k_EUniverseInvalid, k_EAccountTypeInvalid)
    {}

    STEAM_GAMESERVER_CALLBACK(CSteam3Server, OnGSClientApprove, GSClientApprove_t, m_CallbackGSClientApprove)
    {
        auto steamid = pParam->m_SteamID;
        Printf("[Steam] OnGSClientApprove steamid = %i", steamid.ConvertToUint64());
    }

    STEAM_GAMESERVER_CALLBACK(CSteam3Server, OnGSClientDeny, GSClientDeny_t, m_CallbackGSClientDeny)
    {
        auto steamid = pParam->m_SteamID;
        Printf("[Steam] OnGSClientDeny steamid = %i", steamid.ConvertToUint64());
    }

    STEAM_GAMESERVER_CALLBACK(CSteam3Server, OnGSClientKick, GSClientKick_t, m_CallbackGSClientKick)
    {
        auto steamid = pParam->m_SteamID;
        auto reason = pParam->m_eDenyReason;
        Printf("[Steam] OnGSClientKick steamid = %i", steamid.ConvertToUint64(), " reason = ", reason);
    }

    STEAM_GAMESERVER_CALLBACK(CSteam3Server, OnGSPolicyResponse, GSPolicyResponse_t, m_CallbackGSPolicyResponse)
    {
        if (pParam->m_bSecure)
            Printf("[Steam] VAC secure mode is activated.");
        else
            Printf("[Steam] VAC secure mode disabled.");
    }

    STEAM_GAMESERVER_CALLBACK(CSteam3Server, OnLogonSuccess, SteamServersConnected_t, m_CallbackLogonSuccess)
    {
        Printf("[Steam] Connection to Steam servers successful.");

        m_SteamIDGS = SteamGameServer()->GetSteamID();
        //CSteam3Server::SendUpdatedServerDetails();
    
    }

    STEAM_GAMESERVER_CALLBACK(CSteam3Server, OnLogonFailure, SteamServerConnectFailure_t, m_CallbackLogonFailure)
    {
        std::cout << "cout]\n";
        Printf("[Steam]Could not establish connection to Steam servers.");
    
    }
};

#endif