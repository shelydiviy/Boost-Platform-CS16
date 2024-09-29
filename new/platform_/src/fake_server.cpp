#include "fake_server.hpp"

FakeServer::FakeServer(int16_t port, int16_t master_server_port) :
	m_Socket(new Socket()),
	m_MasterServer(new MasterServer()),
	m_QueryPacket(new CDataParser(MAX_SOCKET_BUFFER_LENGTH)),
	m_GamePort(port),
	m_MasterServerPort(master_server_port)
{
	BuildPackets();
	m_Socket->CreateSocket(m_GamePort);
	std::thread(&FakeServer::ListenSocket, this).detach();

	m_MasterServer->Init(m_MasterServerPort, m_GamePort);
}

void FakeServer::ListenSocket()
{
	Printf("Starting listening at %s:%i.\n", IPV4_ADDRESS, m_GamePort);

	CDataParser* pData = new CDataParser(MAX_SOCKET_BUFFER_LENGTH);
	ssize_t bytes;
	CSteamID* SteamID = nullptr;
	bool bResult;

	while (true)
	{
		pData->ClearAllBuf();
		pData->SetOffset(0);

		bytes = m_Socket->Recv(pData->GetFullData(), pData->GetFullSize());

		Printf("Received data of %i bytes length: '%s'\n", bytes, pData->GetCurrentData());

		if (bytes == 206)
		{
			bResult = m_MasterServer->LoginUser(m_Socket->GetSenderAddressInt(), pData->GetCurrentData(), pData->GetCurrentSize(), SteamID);
		
			if (!bResult)
			{
				Printf("Failed to login %s:%i\n", m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
			}
			else
			{
				Printf("User %s:%i has been logged in succesfully!\n", m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
			}
		}

		switch (GetMessageType(pData))
		{
		case QUERY_ENGINE:
			Printf("[Port %i] Received query engine message from %s:%i\n", m_GamePort, m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
			
			if (m_Socket->Send(m_QueryPacket->GetFullData(), m_QueryPacket->GetOffset()) != SOCKET_ERROR)
			{
				Printf("[Port %i] Query packet sent succesfully to %s:%i\n", m_GamePort, m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
			}
			
			break;

		case CVAR_LIST:
			Printf("[Port %i] Received cvar list message from %s:%i\n", m_GamePort, m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
			break;
		
		default: Printf("[Port %i] Received unknown packet from %s:%i\n", m_GamePort, m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
		}
	}

	delete pData;
}

void FakeServer::BuildPackets()
{
	m_QueryPacket->ClearAllBuf();
	m_QueryPacket->SetOffset(0);

	m_QueryPacket->SetByte(0xFF);
	m_QueryPacket->SetByte(0xFF);
	m_QueryPacket->SetByte(0xFF);
	m_QueryPacket->SetByte(0xFF);
	m_QueryPacket->SetByte(0x49); // header
	m_QueryPacket->SetByte(0x30); // protocol
	m_QueryPacket->SetString("MUIE.LAGALEATA.RO"); // host name
	m_QueryPacket->SetString("_aa"); // map
	m_QueryPacket->SetString("cstrike"); // folder
	m_QueryPacket->SetString("Counter-Strike"); // full name of the game name
	m_QueryPacket->SetShort(static_cast<short>(10)); // appid
	m_QueryPacket->SetByte(m_Players); // players
	m_QueryPacket->SetByte(32); // max players
	m_QueryPacket->SetByte(0); // bots
	m_QueryPacket->SetByte(0x64); // server type [0x64 = d (dedicated)]
	m_QueryPacket->SetByte(0x6C); // enviroment [0x6c = l (linux)]
	m_QueryPacket->SetByte(0x00); // visibility [private]
	m_QueryPacket->SetByte(0x01); // VAC [secured]
	m_QueryPacket->SetString("1.1.2.7/Stdio"); // version of the game installed on server
	//m_QueryPacket->SetByte(0x00); // EDF [extra data flag]
	Printf("[Port %i] Packet builded\n", m_GamePort);
}

PacketType FakeServer::GetMessageType(CDataParser* data)
{
	if (
		data->GetByte() != 0xFF ||
		data->GetByte() != 0xFF ||
		data->GetByte() != 0xFF ||
		data->GetByte() != 0xFF
		)
	{
		Printf("Invalid\n");		
		return INVALID;
	}

	PacketType type = INVALID;

	switch (data->GetByte())
	{
	case QUERY_ENGINE: 
		if (std::strcmp(data->GetString(), "Source Engine Query") == 0)
		{
			type = QUERY_ENGINE;
		}

		break;
	}

	return type;
}

void FakeServer::IncreasePlayers()
{
	Printf("[Port %i] Current players online: %i\n", m_GamePort, ++m_Players);
	BuildPackets();
}

void FakeServer::DecreasePlayers()
{
	Printf("[Port %i] Current players online: %i\n", m_GamePort, --m_Players);
	BuildPackets();
}
