#include "Socket.h"

const std::string Socket::GetIPv4Address() const
{
	return inet_ntoa(m_SocketAddrStruct.sin_addr);
}

const uint16_t Socket::GetPort() const
{
	return ntohs(m_SocketAddrStruct.sin_port);
}