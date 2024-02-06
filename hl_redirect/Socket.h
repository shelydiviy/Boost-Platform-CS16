#pragma once
#if !defined _SOCKET
#define _SOCKET

#include <sys/socket.h>
#include <string>
#include <cstdint>
#include <arpa/inet.h>
#include <string.h>

struct Socket {
public:
	const std::string GetIPv4Address() const;
	const uint16_t GetPort() const;

	int m_SocketHandler;
	sockaddr_in m_SocketAddrStruct;
	socklen_t m_SocketAddrSize;
};

#endif