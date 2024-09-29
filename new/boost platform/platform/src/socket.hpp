#pragma once
#ifndef _SOCKET
#define _SOCKET

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <cstring>

enum SocketCode
{
	SOCKET_ERROR_CODE = -1,
	SOCKET_OK_CODE = 0
};

constexpr uint8_t DEFAULT_TIMEOUT_SECONDS = 0;

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

	int Recv(unsigned char* buffer, int buffer_len);
	int Send(unsigned char* buffer, int buffer_len);
	int SendTo(unsigned char* buffer, int buffer_len, sockaddr_in* socket_addr, socklen_t* socket_len);
	void Close();

private:
	int16_t m_Port;

	int m_SocketHandler;
	sockaddr_in m_SenderAddrStruct;
	socklen_t m_SenderAddrSize;

	sockaddr_in m_SocketAddrStruct;
	socklen_t m_SocketAddrSize;
};

#endif