#include "FakeServer.h"

FakeServer::FakeServer(const Socket sock) : m_Socket(sock), m_ClientsMap() {}

const std::string FakeServer::GetIPv4Address() const
{
	return m_Socket.GetIPv4Address();
}

const uint16_t FakeServer::GetPort() const
{
	return m_Socket.GetPort();
}

std::shared_ptr<Socket> FakeServer::AddClient(const std::pair<std::string, uint16_t>&key, std::shared_ptr<Socket> private_socket)
{
    //std::lock_guard<std::mutex>lock(m_ClientsMapMutex);
    m_ClientsMap.emplace(key, private_socket);
    
    return m_ClientsMap[key];
}

std::shared_ptr<Socket> FakeServer::GetClientPrivateSocket(const std::pair<std::string, uint16_t> key)
{
    //std::lock_guard<std::mutex>lock(m_ClientsMapMutex);
    const auto& iterator = m_ClientsMap.find(key);

    if (iterator != m_ClientsMap.end())
    {
        return iterator->second;
    }

    return nullptr;
}
void FakeServer::RemoveClient(const std::pair<std::string, uint16_t>& key)
{
    //std::lock_guard<std::mutex>lock(m_ClientsMapMutex);
    m_ClientsMap.erase(key);
};