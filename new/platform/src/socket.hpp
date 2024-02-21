#pragma once
#ifndef _SOCKET
#define _SOCKET

#include <cstdint>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <cstring>

enum SocketCode
{
	SOCKET_ERROR = -1,
	SOCKET_OK = 0
};

constexpr uint8_t DEFAULT_TIMEOUT_SECONDS = 0;

constexpr uint8_t SOCKET_UDP = SOCK_DGRAM;
constexpr uint8_t SOCKET_TCP = SOCK_STREAM;

class Socket {
public:
	
	Socket();
	Socket(const Socket&) = delete;
	Socket(Socket&&) = delete;
	~Socket();
	void CreateSocket(int16_t port);

	const sockaddr_in* GetAddrStruct() const;
	const sockaddr_in* GetSenderAddrStruct() const;
	const socklen_t* GetSenderAddrStructSize() const;
	
	const char* GetSenderAddressStr() const;
	const uint32_t GetSenderAddressInt() const;
	const uint16_t GetSenderPort() const;

	ssize_t Recv(unsigned char* buffer, int buffer_len);
	ssize_t Send(unsigned char* buffer, int buffer_len);

private:
	int16_t m_Port;

	int m_SocketHandler;
	sockaddr_in m_SenderAddrStruct;
	socklen_t m_SenderAddrSize;

	sockaddr_in m_SocketAddrStruct;
	socklen_t m_SocketAddrSize;
};

#endif