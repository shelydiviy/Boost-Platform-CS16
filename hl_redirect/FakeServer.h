#pragma once
#if !defined _FAKE_SERVER
#define _FAKE_SERVER

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <mutex>
#include "Socket.h"

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }

    size_t operator()(const std::pair<std::string, uint16_t>& p) const {
        auto hash1 = std::hash<std::string>{}(p.first);
        auto hash2 = std::hash<uint16_t>{}(p.second);
        return hash1 ^ hash2;
    }
};

struct FakeServer {
    FakeServer(const Socket sock);
	const std::string GetIPv4Address() const;
	const uint16_t GetPort() const;
	std::shared_ptr<Socket> AddClient(const std::pair<std::string, uint16_t>&key, std::shared_ptr<Socket> private_socket);
	std::shared_ptr<Socket> GetClientPrivateSocket(const std::pair<std::string, uint16_t> key);
    void RemoveClient(const std::pair<std::string, uint16_t>& key);

    std::mutex m_ClientsMapMutex;
    std::unordered_map<std::pair<std::string, uint16_t>, std::shared_ptr<Socket>, hash_pair> m_ClientsMap;
	Socket m_Socket;
	std::string m_Hostname;
	char* m_QueryEnginePacket;
    size_t m_QueryEnginePacketSize;
};
#endif