#include "globals.hpp"
#include "socket.hpp"

Socket::~Socket() {}
Socket::Socket() {}

void Socket::CreateSocket(int16_t port)
{
	m_Port = port;

	// Opening socket
	m_SocketHandler = socket(AF_INET, SOCK_DGRAM, 0);

	if (m_SocketHandler == SOCKET_ERROR)
	{
		Printf("[CRITICAL] Failed to create socket for port %i. Error code %i.\n", m_Port, errno);
		Printf("[CRITICAL] Error message: %s\n", strerror(errno));
		return;
	}

	// Set socket options
	const int opt = 1;

	if (setsockopt(m_SocketHandler, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == SOCKET_ERROR)
	{
		Printf("[CRITICAL] Failed to set socket options for port %i. Error code %i.\n", m_Port, errno);
		Printf("[CRITICAL] Error message: \n", strerror(errno));
		return;
	}

	// Initialize socket structure, setting ipv4 address, port and binding it
	m_SocketAddrSize = sizeof(m_SocketAddrStruct);
	std::memset(&m_SocketAddrStruct, 0, m_SocketAddrSize);

	m_SocketAddrStruct.sin_family = AF_INET;
	m_SocketAddrStruct.sin_port = htons(m_Port);

	inet_pton(AF_INET, IPV4_ADDRESS, &m_SocketAddrStruct.sin_addr);

	if (bind(m_SocketHandler, (sockaddr*)&m_SocketAddrStruct, m_SocketAddrSize) != SOCKET_OK)
	{
		Printf("[CRITICAL] Failed to set bind socket for port %i. Error code %i.\n", m_Port, errno);
		Printf("[CRITICAL] Error message: %s\n", strerror(errno));
		return;
	}

	// Initialize sender socket structure
	m_SenderAddrSize = sizeof(m_SenderAddrStruct);
	std::memset(&m_SenderAddrStruct, 0, m_SenderAddrSize);
}

const sockaddr_in* Socket::GetAddrStruct() const
{
	return &m_SocketAddrStruct;
}

const sockaddr_in* Socket::GetSenderAddrStruct() const
{
	return &m_SenderAddrStruct;
}

const socklen_t* Socket::GetSenderAddrStructSize() const
{
	return &m_SenderAddrSize;
}

const char* Socket::GetSenderAddressStr() const
{
	return inet_ntoa(m_SenderAddrStruct.sin_addr);
}

const uint32_t Socket::GetSenderAddressInt() const
{
	uint32_t ipAddress = 0;

	const char* senderAddress = GetSenderAddressStr();

	if (inet_pton(AF_INET, senderAddress, &ipAddress) != 1)
	{
		Printf("Failed to convert address %s to uint32\n", senderAddress);
		return 0;
	}

	return ipAddress;
}

const uint16_t Socket::GetSenderPort() const
{
	return ntohs(m_SenderAddrStruct.sin_port);
}

ssize_t Socket::Recv(unsigned char* buffer, int buffer_len)
{
	ssize_t bytes = recvfrom(m_SocketHandler, buffer, buffer_len, 0, (sockaddr*) &m_SenderAddrStruct, &m_SenderAddrSize);

	if (bytes >= 0)
		return bytes;

	Printf("[CRITICAL] An error has been occured while receiving data on %s:%i. Error code: %i.\n", m_Port, IPV4_ADDRESS, errno);
	Printf("[CRITICAL] Error message: %s\n", strerror(errno));

	return static_cast<ssize_t>(SOCKET_ERROR);
}

ssize_t Socket::Send(unsigned char* buffer, int buffer_len)
{
	ssize_t bytes = sendto(m_SocketHandler, buffer, buffer_len, 0, (sockaddr *)&m_SenderAddrStruct, m_SenderAddrSize);
	
	if (bytes >= 0)
		return bytes;

	Printf("[CRITICAL] An error has been occured while sending through socket %s:%i to %s:%i. Error code: %i.\n", IPV4_ADDRESS, m_Port, GetSenderAddressStr(), GetSenderPort(), errno);
	Printf("[CRITICAL] Error message: %s\n", strerror(errno));

	return static_cast<ssize_t>(SOCKET_ERROR);
}
