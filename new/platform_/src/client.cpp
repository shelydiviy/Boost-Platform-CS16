#include "client.hpp"

Client::Client(Socket* fake_game_server_socket, const sockaddr_in* socket, const socklen_t* socklen) :
	m_ClientSockAddr(*socket),
	m_ClientSockLen(*socklen),
	m_BridgeSocket(new Socket()),
	m_FakeGameServerSocket(fake_game_server_socket)
{
	m_BridgeSocket->CreateSocket(0);


	m_GameServerSockLen = sizeof(m_GameServerSockAddr);
	std::memset(&m_GameServerSockAddr, 0, m_GameServerSockLen);
	m_GameServerSockAddr.sin_family = AF_INET;
	m_GameServerSockAddr.sin_port = htons(27015);
	inet_pton(AF_INET, "141.95.73.30", &m_GameServerSockAddr.sin_addr);

	m_ClientThread = std::thread(&Client::ListenClientSocket, this);

	m_ShouldRun = true;

	m_ClientThread.detach();

}

Client::~Client()
{
	m_ShouldRun = false;
	delete m_BridgeSocket;
}

void Client::ListenClientSocket()
{
	unsigned char buffer[MAX_SOCKET_BUFFER_LENGTH];
	int size = 0;

	while (m_ShouldRun)
	{
		size = m_BridgeSocket->Recv(buffer, sizeof(buffer));

		m_FakeGameServerSocket->SendTo(buffer, size, &m_ClientSockAddr, &m_ClientSockLen);
	}
}

void Client::SendPacket(unsigned char* buffer, int bufferlen)
{
	int size = m_BridgeSocket->SendTo(buffer, bufferlen, &m_GameServerSockAddr, &m_GameServerSockLen);
}

int16 Client::GetClientPort()
{
	return ntohs(m_ClientSockAddr.sin_port);
}

sockaddr_in* Client::GetClientAddr()
{
	return &m_ClientSockAddr;
}
