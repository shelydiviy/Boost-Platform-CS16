#include "sv_steam3.hpp"
#include "globals.hpp"

CSteam3Server::CSteam3Server() :
    m_CallbackGSClientApprove(this, &CSteam3Server::OnGSClientApprove),
    m_CallbackGSClientDeny(this, &CSteam3Server::OnGSClientDeny),
    m_CallbackGSClientKick(this, &CSteam3Server::OnGSClientKick),
    m_CallbackGSPolicyResponse(this, &CSteam3Server::OnGSPolicyResponse),
    m_CallbackLogonSuccess(this, &CSteam3Server::OnLogonSuccess),
    m_CallbackLogonFailure(this, &CSteam3Server::OnLogonFailure)
{}

void CSteam3Server::OnGSClientApprove(GSClientApprove_t* m_CallbackGSClientApprove)
{
    PlatformManager::get()->SteamOnGSClientApprove(m_CallbackGSClientApprove->m_SteamID.ConvertToUint64());
}

void CSteam3Server::OnGSClientDeny(GSClientDeny_t* m_CallbackGSClientDeny)
{
    PlatformManager::get()->SteamOnGSClientDeny(m_CallbackGSClientDeny->m_SteamID.ConvertToUint64(), m_CallbackGSClientDeny->m_eDenyReason, m_CallbackGSClientDeny->m_rgchOptionalText);
}

void CSteam3Server::OnGSClientKick(GSClientKick_t* m_CallbackGSClientKick)
{
    PlatformManager::get()->SteamOnGSClientDeny(m_CallbackGSClientKick->m_SteamID.ConvertToUint64(), m_CallbackGSClientKick->m_eDenyReason, "");
}

void CSteam3Server::OnGSPolicyResponse(GSPolicyResponse_t* m_CallbackGSPolicyResponse)
{
    // Do nothing, we don't care if it's secured or not.
}

void CSteam3Server::OnLogonSuccess(SteamServersConnected_t* m_CallbackLogonSuccess)
{
    PlatformManager::get()->SteamLogOnSuccess();
}

void CSteam3Server::OnLogonFailure(SteamServerConnectFailure_t* m_CallbackLogonFailure)
{
    PlatformManager::get()->SteamLonOnFailure(m_CallbackLogonFailure->m_eResult);
}